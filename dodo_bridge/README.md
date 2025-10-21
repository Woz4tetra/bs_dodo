# 3D Point Cloud Viewer

A standalone C++ application that connects to ROS via WebSocket ROSBridge to visualize 3D point clouds generated from color and depth camera data.

## Features

- **WebSocket ROSBridge Client**: Connects to ROS without requiring ROS installation
- **Multi-Topic Subscription**: Subscribes to color images, depth images, camera info, and transforms
- **Real-time 3D Visualization**: Renders point clouds in an interactive 3D viewer
- **Camera Transform Handling**: Aligns depth data to color data using transforms from /tf
- **Interactive Controls**: Mouse and keyboard controls for 3D navigation

## Dependencies

Install the required system packages:

```bash
sudo apt update
sudo apt install -y \
    libwebsocketpp-dev \
    libjsoncpp-dev \
    libssl-dev \
    libopencv-dev \
    libglfw3-dev \
    libglew-dev \
    libgl1-mesa-dev
```

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

1. **Start ROSBridge server** (on your ROS system):
   ```bash
   roslaunch rosbridge_server rosbridge_websocket.launch
   ```

2. **Run the point cloud viewer**:
   ```bash
   ./build/image_delay_subscriber
   ```

3. **Controls**:
   - **Mouse drag**: Rotate camera view
   - **Mouse scroll**: Zoom in/out
   - **R key**: Reset camera view
   - **ESC key**: Exit application

## Subscribed Topics

- `/camera/color/image_raw/compressed` - Color camera images
- `/camera/depth/image_rect_raw/compressedDepth` - Depth camera images  
- `/camera/color/camera_info` - Camera intrinsic parameters
- `/tf` - Transform data for camera alignment

## Configuration

Edit `src/main.cpp` to change:
- **ROSBridge server address**: Default is `192.168.50.169:9090`
- **Topic names**: Modify the topic strings in the main function
- **Camera parameters**: Default intrinsics are set in main()

## Architecture

### Core Components

- **RosClient**: WebSocket client for ROSBridge communication
- **TopicSubscriber**: Manages ROS topic subscriptions and message routing
- **PointCloudViewer**: OpenGL-based 3D visualization engine
- **Point cloud generation**: Converts color + depth data to 3D colored points

### Point Cloud Pipeline

1. **Data Acquisition**: Receives color images, depth images, and camera parameters
2. **Alignment**: Uses transform data to align depth pixels to color pixels
3. **3D Projection**: Projects 2D pixels to 3D space using camera intrinsics
4. **Visualization**: Renders colored 3D points in real-time

## Troubleshooting

### OpenGL/Display Issues
```bash
# For headless systems, ensure X11 forwarding or virtual display
export DISPLAY=:0
# Or use xvfb for virtual display
xvfb-run -a ./build/image_delay_subscriber
```

### ROSBridge Connection Issues
- Verify ROSBridge server is running: `rostopic list`
- Check network connectivity: `ping 192.168.50.169`
- Confirm topics are publishing: `rostopic hz /camera/color/image_raw/compressed`

### Camera Topic Issues
- Verify camera topics exist: `rostopic list | grep camera`
- Check topic message types: `rostopic info /camera/color/image_raw/compressed`
- Test image data: `rostopic echo /camera/color/image_raw/compressed --noarr`

## Performance Notes

- Point clouds are subsampled (every 2nd pixel) for performance
- Points beyond 10 meters are filtered out
- Typical performance: 30-60 FPS with 640x480 images
- Memory usage scales with image resolution and point density