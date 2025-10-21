#!/usr/bin/env python3
"""
Ultra low-latency LIDAR visualization using minimal OpenCV operations.
This version prioritizes speed over visual quality for lag measurement.
"""

import logging
import time
import math
import threading

import cv2
import numpy as np
import roslibpy

# Configure logging
fmt = "%(asctime)s %(levelname)8s: %(message)s"
logging.basicConfig(format=fmt, level=logging.INFO)
log = logging.getLogger(__name__)

class FastLidarVisualizer:
    def __init__(self, ros_host="192.168.50.169", ros_port=9090):
        # Minimal display parameters for maximum speed
        self.window_name = "Fast LIDAR Scan"
        self.canvas_size = 600
        self.center = self.canvas_size // 2
        self.scale = 20.0  # pixels per meter
        
        # Performance tracking
        self.scan_count = 0
        self.start_time = time.time()
        
        # Thread safety - minimal locking
        self.lock = threading.Lock()
        self.points = []
        self.current_delay = 0
        self.current_seq = 0
        
        # ROS setup
        self.client = roslibpy.Ros(host=ros_host, port=ros_port)
        self.subscriber = roslibpy.Topic(self.client, "/laser/scan", "sensor_msgs/LaserScan")
        
        # Pre-allocate canvas for speed
        self.canvas = np.zeros((self.canvas_size, self.canvas_size, 3), dtype=np.uint8)
        
        log.info("Fast LIDAR Visualizer initialized")
    
    def receive_scan(self, message):
        """Ultra-fast scan processing"""
        try:
            current_time = time.time()
            
            # Quick delay calculation
            header = message.get('header', {})
            seq = header.get('seq', 0)
            timestamp_data = header.get('stamp', {})
            
            if isinstance(timestamp_data, dict):
                ros_time = timestamp_data.get('secs', 0) + timestamp_data.get('nsecs', 0) * 1e-9
            else:
                ros_time = float(timestamp_data) if timestamp_data else 0
                
            delay = current_time - ros_time if ros_time > 0 else 0
            
            # Fast point conversion
            ranges = message.get('ranges', [])
            angle_min = message.get('angle_min', -math.pi)
            angle_increment = message.get('angle_increment', 0.01)
            
            # Convert to screen coordinates in one pass
            points = []
            for i, r in enumerate(ranges):
                if r is not None and not math.isinf(r) and not math.isnan(r) and 0.1 < r < 15.0:  # Robust range check
                    angle = angle_min + i * angle_increment - math.pi/2  # Forward is up
                    x = int(self.center + r * self.scale * math.cos(angle))
                    y = int(self.center + r * self.scale * math.sin(angle))
                    if 10 < x < self.canvas_size-10 and 10 < y < self.canvas_size-10:
                        points.append((x, y))
            
            # Atomic update
            with self.lock:
                self.points = points
                self.current_delay = delay
                self.current_seq = seq
                self.scan_count += 1
            
        except Exception as e:
            log.error(f"Scan processing error: {e}")
    
    def run_visualization(self):
        """Ultra-fast rendering loop"""
        cv2.namedWindow(self.window_name, cv2.WINDOW_AUTOSIZE)
        
        frame_count = 0
        last_fps_time = time.time()
        
        log.info("Fast visualization running. Press 'q' to quit.")
        
        while True:
            # Clear canvas (fastest method)
            self.canvas.fill(0)
            
            # Get points with minimal locking
            with self.lock:
                points = self.points[:]  # Copy list
                delay = self.current_delay
                seq = self.current_seq
            
            # Draw points (fastest method)
            for x, y in points:
                self.canvas[y-1:y+2, x-1:x+2] = [0, 255, 0]  # 3x3 green squares
            
            # Minimal text info
            fps_text = f"FPS: {frame_count/(time.time()-last_fps_time+0.001):.0f}"
            delay_text = f"Delay: {delay*1000:.0f}ms"
            
            cv2.putText(self.canvas, fps_text, (10, 30), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 1)
            cv2.putText(self.canvas, delay_text, (10, 60), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, 
                       (0, 0, 255) if delay > 0.1 else (255, 255, 255), 1)
            cv2.putText(self.canvas, f"Seq: {seq}", (10, 90), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 1)
            
            # Show frame
            cv2.imshow(self.window_name, self.canvas)
            
            # Quick exit check
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
            
            frame_count += 1
            if frame_count % 30 == 0:  # Reset FPS counter every 30 frames
                last_fps_time = time.time()
                frame_count = 0
        
        cv2.destroyAllWindows()
    
    def start(self):
        """Start everything"""
        try:
            self.client.run()
            self.subscriber.subscribe(self.receive_scan)
            self.run_visualization()
        except KeyboardInterrupt:
            pass
        finally:
            try:
                self.subscriber.unsubscribe()
                self.client.terminate()
            except Exception:
                pass

def main():
    visualizer = FastLidarVisualizer()
    visualizer.start()

if __name__ == "__main__":
    main()