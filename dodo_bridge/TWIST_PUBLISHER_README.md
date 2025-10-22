# Twist Publisher Example

This is a simple example program that demonstrates how to publish Twist messages using miniroscpp.

## What it does

The `twist_publisher` executable:
- Connects to a ROS master using miniroscpp
- Publishes `geometry_msgs/Twist` messages on the `/cmd_vel` topic
- Sends different movement commands every second:
  1. Move Forward (linear.x = 0.5)
  2. Turn Right (angular.z = -0.5) 
  3. Move Backward (linear.x = -0.3)
  4. Turn Left (angular.z = 0.5)
- Repeats this pattern continuously until stopped
- Sends a stop command (all zeros) before shutting down

## Building

```bash
cd /home/ben/bs_dodo/dodo_bridge/build
make twist_publisher
```

## Running

### Option 1: With local rosmaster
```bash
cd /home/ben/bs_dodo/dodo_bridge/build
./twist_publisher
```

### Option 2: With remote ROS master
To connect to a remote ROS master, specify the master URI and optionally ROS IP:
```bash
cd /home/ben/bs_dodo/dodo_bridge/build
./twist_publisher --master-uri http://192.168.1.100:11311 --ros-ip 192.168.1.50
```

### Option 3: With embedded miniroscore
For a standalone setup, you can use miniroscore:
```bash
# Terminal 1: Start miniroscore
cd /home/ben/bs_dodo/dodo_bridge/build
./thirdparty/miniroscpp/bin/miniroscore

# Terminal 2: Run twist publisher (connecting to local miniroscore)
cd /home/ben/bs_dodo/dodo_bridge/build
./twist_publisher --master-uri http://localhost:11311
```

### Option 4: Using environment variables
You can also set the ROS Master URI and IP via environment variables:
```bash
export ROS_MASTER_URI=http://192.168.1.100:11311
export ROS_IP=192.168.1.50
cd /home/ben/bs_dodo/dodo_bridge/build
./twist_publisher
```

## Monitoring messages

You can monitor the published messages using:

```bash
# If using miniroscore, use minibag:
cd /home/ben/bs_dodo/dodo_bridge/build
./bin/minibag record /cmd_vel

# Or if you have ros tools:
rostopic echo /cmd_vel
```

## Code Structure

The example demonstrates:
- Basic miniroscpp initialization with `miniros::init()`
- Creating a NodeHandle with `miniros::NodeHandle`
- Setting up a publisher with `nh.advertise<geometry_msgs::Twist>()`
- Creating and publishing messages with `twist_pub.publish()`
- Using `miniros::Rate` for timing control
- Proper cleanup with signal handling and `miniros::shutdown()`

This is a complete, self-contained example that can be used as a template for other ROS publishers using miniroscpp.