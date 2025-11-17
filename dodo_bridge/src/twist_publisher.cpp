#include <miniros/ros.h>
#include <geometry_msgs/Twist.hxx>
#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <map>
#include <string>

// Global flag for signal handling
volatile bool running = true;

void signal_handler(int signal)
{
    std::cout << "\nReceived signal " << signal << ". Shutting down..." << std::endl;
    running = false;
}

void print_usage(const char* program_name)
{
    std::cout << "Usage: " << program_name << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --master-uri <uri>    ROS Master URI (e.g., http://192.168.1.100:11311)" << std::endl;
    std::cout << "  --ros-ip <ip>         ROS IP address for this node (e.g., 192.168.1.50)" << std::endl;
    std::cout << "  -h, --help           Show this help message" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << program_name << " --master-uri http://192.168.1.100:11311 --ros-ip 192.168.1.50" << std::endl;
    std::cout << "  " << program_name << " --master-uri http://192.168.1.100:11311" << std::endl;
}

int main(int argc, char** argv)
{
    // Set up signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Parse command line arguments
    std::string master_uri;
    std::string ros_ip;
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--master-uri" && i + 1 < argc)
        {
            master_uri = argv[i + 1];
            i++; // Skip next argument since we consumed it
        }
        else if (arg == "--ros-ip" && i + 1 < argc)
        {
            ros_ip = argv[i + 1];
            i++; // Skip next argument since we consumed it
        }
        else if (arg == "-h" || arg == "--help")
        {
            print_usage(argv[0]);
            return 0;
        }
    }

    std::cout << "Starting Twist Publisher..." << std::endl;

    // Set ROS Master URI if provided
    if (!master_uri.empty())
    {
        std::cout << "Using ROS Master URI: " << master_uri << std::endl;
        setenv("ROS_MASTER_URI", master_uri.c_str(), 1);
    }
    else
    {
        // Check if ROS_MASTER_URI is already set
        const char* existing_uri = getenv("ROS_MASTER_URI");
        if (existing_uri)
        {
            std::cout << "Using ROS Master URI from environment: " << existing_uri << std::endl;
        }
        else
        {
            std::cout << "No ROS Master URI specified. Using default (localhost:11311)" << std::endl;
            setenv("ROS_MASTER_URI", "http://localhost:11311", 1);
        }
    }

    // Set ROS IP if provided
    if (!ros_ip.empty())
    {
        std::cout << "Using ROS IP: " << ros_ip << std::endl;
        setenv("ROS_IP", ros_ip.c_str(), 1);
    }
    else
    {
        // Check if ROS_IP is already set
        const char* existing_ip = getenv("ROS_IP");
        if (existing_ip)
        {
            std::cout << "Using ROS IP from environment: " << existing_ip << std::endl;
        }
        else
        {
            std::cout << "No ROS IP specified. ROS will auto-detect network interface." << std::endl;
        }
    }

    // Initialize miniros with remapping support
    std::map<std::string, std::string> remappings;
    if (!master_uri.empty())
    {
        remappings["__master"] = master_uri;
    }
    
    if (!remappings.empty())
    {
        miniros::init(remappings, "twist_publisher");
    }
    else
    {
        miniros::init(argc, argv, "twist_publisher");
    }

    // Create NodeHandle
    miniros::NodeHandle nh;

    // Create publisher for cmd_vel topic
    miniros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("/dodobot/cmd_vel_teleop", 1);

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