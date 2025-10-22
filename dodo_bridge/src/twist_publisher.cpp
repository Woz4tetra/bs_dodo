#include <miniros/ros.h>
#include <geometry_msgs/Twist.hxx>
#include <iostream>
#include <signal.h>

// Global flag for signal handling
volatile bool running = true;

void signal_handler(int signal)
{
    std::cout << "\nReceived signal " << signal << ". Shutting down..." << std::endl;
    running = false;
}

int main(int argc, char** argv)
{
    // Set up signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::cout << "Starting Twist Publisher..." << std::endl;

    // Initialize miniros
    miniros::init(argc, argv, "twist_publisher");

    // Create NodeHandle
    miniros::NodeHandle nh;

    // Create publisher for cmd_vel topic
    miniros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    std::cout << "Publishing Twist messages on /cmd_vel topic every second..." << std::endl;
    std::cout << "Press Ctrl+C to stop." << std::endl;

    // Set up rate for 1 Hz (once per second)
    miniros::Rate rate(1.0);

    // Counter for varying the commands
    int counter = 0;

    while (running && miniros::ok())
    {
        // Create a Twist message
        geometry_msgs::Twist twist_msg;

        // Create different movement patterns based on counter
        switch (counter % 4)
        {
            case 0:
                // Move forward
                twist_msg.linear.x = 0.5;
                twist_msg.linear.y = 0.0;
                twist_msg.linear.z = 0.0;
                twist_msg.angular.x = 0.0;
                twist_msg.angular.y = 0.0;
                twist_msg.angular.z = 0.0;
                std::cout << "Publishing: Move Forward (linear.x = 0.5)" << std::endl;
                break;
            case 1:
                // Turn right
                twist_msg.linear.x = 0.0;
                twist_msg.linear.y = 0.0;
                twist_msg.linear.z = 0.0;
                twist_msg.angular.x = 0.0;
                twist_msg.angular.y = 0.0;
                twist_msg.angular.z = -0.5;
                std::cout << "Publishing: Turn Right (angular.z = -0.5)" << std::endl;
                break;
            case 2:
                // Move backward
                twist_msg.linear.x = -0.3;
                twist_msg.linear.y = 0.0;
                twist_msg.linear.z = 0.0;
                twist_msg.angular.x = 0.0;
                twist_msg.angular.y = 0.0;
                twist_msg.angular.z = 0.0;
                std::cout << "Publishing: Move Backward (linear.x = -0.3)" << std::endl;
                break;
            case 3:
                // Turn left
                twist_msg.linear.x = 0.0;
                twist_msg.linear.y = 0.0;
                twist_msg.linear.z = 0.0;
                twist_msg.angular.x = 0.0;
                twist_msg.angular.y = 0.0;
                twist_msg.angular.z = 0.5;
                std::cout << "Publishing: Turn Left (angular.z = 0.5)" << std::endl;
                break;
        }

        // Publish the message
        twist_pub.publish(twist_msg);

        // Process any ROS callbacks
        miniros::spinOnce();

        // Increment counter
        counter++;

        // Sleep to maintain 1 Hz rate
        rate.sleep();
    }

    std::cout << "Shutting down Twist Publisher..." << std::endl;
    
    // Send stop command before shutting down
    geometry_msgs::Twist stop_msg;
    // All values default to 0.0, which means stop
    twist_pub.publish(stop_msg);
    
    miniros::shutdown();

    return 0;
}