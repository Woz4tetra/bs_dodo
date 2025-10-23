#include <miniros/ros.h>
#include <db_parsing/DodobotNotify.hxx>
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
    std::cout << "  --message <msg>       Custom message to publish" << std::endl;
    std::cout << "  --level <level>       Log level (0=INFO, 1=WARN, 2=ERROR)" << std::endl;
    std::cout << "  --timeout <ms>        Timeout in milliseconds" << std::endl;
    std::cout << "  -h, --help           Show this help message" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << program_name << " --master-uri http://192.168.1.100:11311 --message \"Hello World\"" << std::endl;
    std::cout << "  " << program_name << " --message \"Warning message\" --level 1 --timeout 5000" << std::endl;
}

int main(int argc, char** argv)
{
    // Set up signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Parse command line arguments
    std::string master_uri;
    std::string ros_ip;
    std::string message_text = "Test notification from dodobot";
    int32_t level = db_parsing::DodobotNotify::INFO;
    uint32_t timeout = 3000; // Default 3 seconds

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
        else if (arg == "--message" && i + 1 < argc)
        {
            message_text = argv[i + 1];
            i++; // Skip next argument since we consumed it
        }
        else if (arg == "--level" && i + 1 < argc)
        {
            level = std::stoi(argv[i + 1]);
            i++; // Skip next argument since we consumed it
        }
        else if (arg == "--timeout" && i + 1 < argc)
        {
            timeout = std::stoul(argv[i + 1]);
            i++; // Skip next argument since we consumed it
        }
        else if (arg == "-h" || arg == "--help")
        {
            print_usage(argv[0]);
            return 0;
        }
    }

    std::cout << "Starting DodobotNotify Publisher..." << std::endl;

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
        miniros::init(remappings, "dodobot_notify_publisher");
    }
    else
    {
        miniros::init(argc, argv, "dodobot_notify_publisher");
    }

    // Create NodeHandle
    miniros::NodeHandle nh;

    // Create publisher for /dodobot/notify topic
    miniros::Publisher notify_pub = nh.advertise<db_parsing::DodobotNotify>("/dodobot/notify", 1);

    std::cout << "Publishing DodobotNotify messages on /dodobot/notify topic every 2 seconds..." << std::endl;
    std::cout << "Message: \"" << message_text << "\"" << std::endl;
    std::cout << "Level: " << level << " (" << 
        (level == db_parsing::DodobotNotify::INFO ? "INFO" :
         level == db_parsing::DodobotNotify::WARN ? "WARN" :
         level == db_parsing::DodobotNotify::ERROR ? "ERROR" : "UNKNOWN") << ")" << std::endl;
    std::cout << "Timeout: " << timeout << " ms" << std::endl;
    std::cout << "Press Ctrl+C to stop." << std::endl;

    // Set up rate for 0.5 Hz (once per 2 seconds)
    miniros::Rate rate(0.5);

    // Counter for message variation
    int counter = 0;

    while (running && miniros::ok())
    {
        // Create a DodobotNotify message
        db_parsing::DodobotNotify notify_msg;
        
        // Use provided message or create varying messages based on counter
        if (argc > 1) // If command line arguments were provided, use them
        {
            notify_msg.message = message_text;
            notify_msg.level = level;
            notify_msg.timeout = timeout;
        }
        else // Create varying test messages
        {
            switch (counter % 3)
            {
                case 0:
                    notify_msg.message = "System startup complete";
                    notify_msg.level = db_parsing::DodobotNotify::INFO;
                    notify_msg.timeout = 2000;
                    break;
                case 1:
                    notify_msg.message = "Battery level low";
                    notify_msg.level = db_parsing::DodobotNotify::WARN;
                    notify_msg.timeout = 5000;
                    break;
                case 2:
                    notify_msg.message = "Navigation obstacle detected";
                    notify_msg.level = db_parsing::DodobotNotify::ERROR;
                    notify_msg.timeout = 10000;
                    break;
            }
        }

        // Display what we're publishing
        std::string level_str = (notify_msg.level == db_parsing::DodobotNotify::INFO ? "INFO" :
                                notify_msg.level == db_parsing::DodobotNotify::WARN ? "WARN" :
                                notify_msg.level == db_parsing::DodobotNotify::ERROR ? "ERROR" : "UNKNOWN");
        
        std::cout << "Publishing [" << level_str << "] \"" << notify_msg.message 
                  << "\" (timeout: " << notify_msg.timeout << "ms)" << std::endl;

        // Publish the message
        notify_pub.publish(notify_msg);

        // Process any ROS callbacks
        miniros::spinOnce();

        // Increment counter
        counter++;

        // Sleep to maintain rate
        rate.sleep();
    }

    std::cout << "Shutting down DodobotNotify Publisher..." << std::endl;
    
    miniros::shutdown();

    return 0;
}