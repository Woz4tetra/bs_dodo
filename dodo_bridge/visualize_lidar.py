#!/usr/bin/env python3
"""
Real-time LIDAR visualization using OpenCV for minimal latency.
This script subscribes to laser scan data and displays it as a polar plot
with timestamp information to measure lag.
"""

import logging
import time
import math
import threading
from collections import deque

import cv2
import numpy as np
import roslibpy

# Configure logging
fmt = "%(asctime)s %(levelname)8s: %(message)s"
logging.basicConfig(format=fmt, level=logging.INFO)
log = logging.getLogger(__name__)

class LidarVisualizer:
    def __init__(self, ros_host="192.168.50.169", ros_port=9090):
        # Display parameters
        self.window_name = "LIDAR Scan Visualization"
        self.canvas_size = 800
        self.center = self.canvas_size // 2
        self.max_range = 10.0  # meters - will be updated from scan data
        self.scale_factor = 300  # pixels per meter
        
        # Performance tracking
        self.frame_times = deque(maxlen=100)
        self.delays = deque(maxlen=100)
        self.last_update_time = time.time()
        
        # Thread safety
        self.lock = threading.Lock()
        self.latest_scan_data = None
        
        # ROS setup
        self.client = roslibpy.Ros(host=ros_host, port=ros_port)
        self.subscriber = roslibpy.Topic(self.client, "/laser/scan", "sensor_msgs/LaserScan")
        
        # Color scheme
        self.bg_color = (20, 20, 20)  # Dark background
        self.scan_color = (0, 255, 0)  # Green for scan points
        self.text_color = (255, 255, 255)  # White text
        self.grid_color = (50, 50, 50)  # Dark gray grid
        
        log.info("LIDAR Visualizer initialized")
    
    def receive_scan(self, message):
        """Callback for receiving LIDAR scan data"""
        try:
            current_time = time.time()
            
            # Extract header info
            header = message.get('header', {})
            seq = header.get('seq', 'unknown')
            
            # Calculate delay
            timestamp_data = header.get('stamp', {})
            if isinstance(timestamp_data, dict):
                ros_time = timestamp_data.get('secs', 0) + timestamp_data.get('nsecs', 0) * 1e-9
            else:
                ros_time = float(timestamp_data) if timestamp_data else 0
                
            delay = current_time - ros_time if ros_time > 0 else 0
            
            # Extract scan data
            ranges = message.get('ranges', [])
            angle_min = message.get('angle_min', -math.pi)
            angle_max = message.get('angle_max', math.pi)
            angle_increment = message.get('angle_increment', 0.01)
            range_min = message.get('range_min', 0.1)
            range_max = message.get('range_max', 10.0)
            
            # Update max range for scaling
            self.max_range = min(range_max, 15.0)  # Cap at 15m for visualization
            self.scale_factor = (self.canvas_size * 0.4) / self.max_range
            
            # Thread-safe update of scan data
            with self.lock:
                self.latest_scan_data = {
                    'ranges': ranges,
                    'angle_min': angle_min,
                    'angle_max': angle_max,
                    'angle_increment': angle_increment,
                    'range_min': range_min,
                    'range_max': range_max,
                    'seq': seq,
                    'delay': delay,
                    'receive_time': current_time
                }
            
            # Track performance
            self.delays.append(delay)
            
            log.info(f"Scan seq={seq}, points={len(ranges)}, delay={delay:.3f}s")
            
        except Exception as e:
            log.error(f"Error processing scan message: {e}")
            import traceback
            traceback.print_exc()
    
    def draw_grid(self, canvas):
        """Draw circular grid for range reference"""
        # Draw range circles
        for r in range(1, int(self.max_range) + 1):
            radius = int(r * self.scale_factor)
            if radius < self.canvas_size // 2:
                cv2.circle(canvas, (self.center, self.center), radius, self.grid_color, 1)
                
                # Add range labels
                text = f"{r}m"
                text_size = cv2.getTextSize(text, cv2.FONT_HERSHEY_SIMPLEX, 0.4, 1)[0]
                cv2.putText(canvas, text, 
                           (self.center + radius - text_size[0]//2, self.center - 5),
                           cv2.FONT_HERSHEY_SIMPLEX, 0.4, self.grid_color, 1)
        
        # Draw angle lines (every 30 degrees)
        for angle_deg in range(0, 360, 30):
            angle_rad = math.radians(angle_deg)
            end_x = int(self.center + (self.canvas_size // 2) * math.cos(angle_rad))
            end_y = int(self.center + (self.canvas_size // 2) * math.sin(angle_rad))
            cv2.line(canvas, (self.center, self.center), (end_x, end_y), self.grid_color, 1)
    
    def draw_scan_data(self, canvas, scan_data):
        """Draw the LIDAR scan points"""
        ranges = scan_data['ranges']
        angle_min = scan_data['angle_min']
        angle_increment = scan_data['angle_increment']
        range_min = scan_data['range_min']
        range_max = scan_data['range_max']
        
        points = []
        
        for i, range_val in enumerate(ranges):
            if (range_val is not None and not math.isinf(range_val) and not math.isnan(range_val) and 
                range_min <= range_val <= range_max):
                # Calculate angle (note: LIDAR coordinate system vs screen coordinates)
                angle = angle_min + i * angle_increment
                
                # Convert to screen coordinates
                # Rotate by -90 degrees to make forward direction up
                screen_angle = angle - math.pi/2
                
                # Scale range to pixels
                scaled_range = range_val * self.scale_factor
                
                x = int(self.center + scaled_range * math.cos(screen_angle))
                y = int(self.center + scaled_range * math.sin(screen_angle))
                
                # Check bounds
                if 0 <= x < self.canvas_size and 0 <= y < self.canvas_size:
                    points.append((x, y))
        
        # Draw scan points
        for point in points:
            cv2.circle(canvas, point, 2, self.scan_color, -1)
        
        # Draw connecting lines for better visualization
        if len(points) > 1:
            for i in range(len(points) - 1):
                # Only connect nearby points to avoid long lines across obstacles
                dist = math.sqrt((points[i+1][0] - points[i][0])**2 + 
                               (points[i+1][1] - points[i][1])**2)
                if dist < 20:  # pixels
                    cv2.line(canvas, points[i], points[i+1], self.scan_color, 1)
    
    def draw_stats(self, canvas, scan_data):
        """Draw performance statistics on the canvas"""
        current_time = time.time()
        self.frame_times.append(current_time)
        
        # Calculate FPS
        if len(self.frame_times) > 1:
            fps = len(self.frame_times) / (self.frame_times[-1] - self.frame_times[0])
        else:
            fps = 0
        
        # Calculate average delay
        avg_delay = sum(self.delays) / len(self.delays) if self.delays else 0
        max_delay = max(self.delays) if self.delays else 0
        
        # Prepare stats text
        stats = [
            f"Seq: {scan_data['seq']}",
            f"Points: {len(scan_data['ranges'])}",
            f"Current Delay: {scan_data['delay']:.3f}s",
            f"Avg Delay: {avg_delay:.3f}s",
            f"Max Delay: {max_delay:.3f}s", 
            f"Display FPS: {fps:.1f}",
            f"Range: {self.max_range:.1f}m"
        ]
        
        # Draw background for stats
        stats_bg = np.zeros((len(stats) * 25 + 20, 250, 3), dtype=np.uint8)
        stats_bg[:] = (0, 0, 0)
        
        # Draw stats text
        y_offset = 20
        for i, stat in enumerate(stats):
            color = self.text_color
            # Highlight high delays in red
            if "Delay:" in stat and scan_data['delay'] > 0.1:
                color = (0, 0, 255)  # Red for high delay
            
            cv2.putText(canvas, stat, (10, y_offset + i * 25), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.6, color, 2)
        
        # Draw center crosshair
        cv2.line(canvas, (self.center - 10, self.center), (self.center + 10, self.center), 
                self.text_color, 2)
        cv2.line(canvas, (self.center, self.center - 10), (self.center, self.center + 10), 
                self.text_color, 2)
    
    def run_visualization(self):
        """Main visualization loop"""
        cv2.namedWindow(self.window_name, cv2.WINDOW_AUTOSIZE)
        
        log.info("Starting visualization loop. Press 'q' or ESC to quit.")
        
        while True:
            # Create blank canvas
            canvas = np.full((self.canvas_size, self.canvas_size, 3), 
                           self.bg_color, dtype=np.uint8)
            
            # Draw grid
            self.draw_grid(canvas)
            
            # Get latest scan data
            with self.lock:
                scan_data = self.latest_scan_data
            
            if scan_data:
                # Draw scan data
                self.draw_scan_data(canvas, scan_data)
                
                # Draw statistics
                self.draw_stats(canvas, scan_data)
            else:
                # No data received yet
                cv2.putText(canvas, "Waiting for LIDAR data...", 
                           (self.center - 100, self.center), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.8, self.text_color, 2)
            
            # Display canvas
            cv2.imshow(self.window_name, canvas)
            
            # Handle key presses
            key = cv2.waitKey(1) & 0xFF
            if key == ord('q') or key == 27:  # 'q' or ESC
                break
            elif key == ord('r'):  # Reset statistics
                self.frame_times.clear()
                self.delays.clear()
                log.info("Statistics reset")
        
        cv2.destroyAllWindows()
        log.info("Visualization stopped")
    
    def start(self):
        """Start the ROS client and visualization"""
        try:
            # Connect to ROS
            log.info("Connecting to ROS...")
            self.client.run()
            
            # Subscribe to laser scan
            self.subscriber.subscribe(self.receive_scan)
            log.info("Subscribed to /laser/scan topic")
            
            # Start visualization in main thread
            self.run_visualization()
            
        except KeyboardInterrupt:
            log.info("Received interrupt signal")
        except Exception as e:
            log.error(f"Error in main loop: {e}")
            import traceback
            traceback.print_exc()
        finally:
            # Cleanup
            try:
                self.subscriber.unsubscribe()
                self.client.terminate()
            except Exception:
                pass
            log.info("Cleanup complete")

def main():
    """Main entry point"""
    print("LIDAR Real-time Visualizer")
    print("Controls:")
    print("  q or ESC: Quit")
    print("  r: Reset statistics")
    print("")
    
    visualizer = LidarVisualizer()
    visualizer.start()

if __name__ == "__main__":
    main()