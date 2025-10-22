# LIDAR Visualizer

A real-time LIDAR scan visualization program using miniroscpp and OpenCV.

## What it does

The `lidar_visualizer` executable:
- Subscribes to `/laser/scan` topic (`sensor_msgs/LaserScan` messages)
- Displays LIDAR scan data in real-time using OpenCV
- Shows performance statistics including delays and frame rates
- Provides an interactive polar plot visualization similar to the Python version

## Features

### Visualization
- **Polar plot display** - Shows LIDAR data in traditional polar coordinate system
- **Range circles** - Configurable range rings for distance reference
- **Angle lines** - 30-degree angle reference lines
- **Color-coded display** - Green scan points with connecting lines
- **Center crosshair** - Shows robot position and orientation

### Performance Monitoring
- **Real-time delay calculation** - Shows message delays from ROS timestamp
- **Statistics display** - Current, average, and maximum delays
- **Frame rate monitoring** - Display FPS tracking
- **Performance highlighting** - High delays shown in red

### Interactive Controls
- **q or ESC**: Quit application
- **r**: Reset statistics (clears delay and frame rate history)

## Building

```bash
cd /home/ben/bs_dodo/dodo_bridge/build
make lidar_visualizer
```

## Usage

### Basic Usage
```bash
cd /home/ben/bs_dodo/dodo_bridge/build
./lidar_visualizer
```

### With Remote ROS Master
```bash
./lidar_visualizer --master-uri http://192.168.50.169:11311 --ros-ip 192.168.50.212
```

### Using Environment Variables
```bash
export ROS_MASTER_URI=http://192.168.50.169:11311
export ROS_IP=192.168.50.212
./lidar_visualizer
```

## Command Line Options

- `--master-uri <uri>`: ROS Master URI (e.g., `http://192.168.1.100:11311`)
- `--ros-ip <ip>`: ROS IP address for this node (e.g., `192.168.1.50`)
- `-h, --help`: Show help message

## Display Elements

### Main View
- **Dark background** for better visibility
- **Green scan points** representing detected obstacles/objects
- **Connecting lines** between nearby points for better visualization
- **Range circles** showing 1m, 2m, 3m, etc. distances
- **Angle reference lines** every 30 degrees

### Statistics Panel (Top-left)
- **Seq**: ROS message sequence number
- **Points**: Number of valid laser scan points
- **Current Delay**: Delay of the most recent message
- **Avg Delay**: Average delay over recent messages
- **Max Delay**: Maximum delay observed
- **Display FPS**: Visualization frame rate
- **Range**: Maximum range being displayed

### Coordinate System
- **Forward direction**: Up on screen
- **Robot position**: Center of display
- **Rotation**: Standard ROS coordinate system (counter-clockwise positive)

## Technical Details

### Message Processing
- Native `sensor_msgs/LaserScan` message handling
- Automatic range and angle scaling
- Invalid point filtering (NaN, infinity, out-of-range)
- Thread-safe data handling between ROS callbacks and visualization

### Performance Optimizations
- Separate visualization thread for smooth display
- Efficient OpenCV drawing operations
- Configurable frame rate limiting
- Statistics buffering with automatic cleanup

### Coordinate Transformations
- Converts from polar LIDAR coordinates to screen coordinates
- Applies -90° rotation to align forward direction with screen up
- Automatic scaling based on maximum range
- Boundary checking for display limits

## Comparison to Python Version

This C++ implementation provides:
- **Better performance** - Native compiled code vs interpreted Python
- **Lower latency** - Direct ROS message handling without websocket overhead
- **Reduced dependencies** - Only requires miniroscpp and OpenCV
- **Memory efficiency** - More efficient data structures and processing
- **Integration** - Consistent with other C++ tools in the project

## Troubleshooting

### No LIDAR Data
- Check if `/laser/scan` topic is being published: `rostopic list`
- Verify message type: `rostopic info /laser/scan`
- Check ROS network connectivity

### High Delays
- Monitor network latency between LIDAR source and visualizer
- Check system load and available CPU resources
- Verify ROS_MASTER_URI and ROS_IP settings for optimal routing

### Display Issues
- Ensure OpenCV is properly installed with GUI support
- Check X11 forwarding if running over SSH
- Verify display permissions and environment variables

## Future Enhancements

Possible improvements:
- Configurable color schemes
- Zoom and pan functionality
- Data recording/playback capabilities
- Multi-LIDAR support
- Obstacle detection overlays
- Export to image/video formats