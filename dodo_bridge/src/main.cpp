#include "point_cloud_viewer.h"
#include <miniros/ros.h>
#include <sensor_msgs/CompressedImage.hxx>
#include <sensor_msgs/CameraInfo.hxx>
#include <tf2_msgs/TFMessage.hxx>
#include <iostream>
#include <chrono>
#include <thread>
#include <signal.h>
#include <iomanip>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <mutex>

// Global flag for signal handling
volatile bool running = true;

// Global data storage
struct GlobalData
{
    cv::Mat latest_color_image;
    cv::Mat latest_depth_image;
    CameraIntrinsics color_intrinsics;
    CameraIntrinsics depth_intrinsics;
    Transform depth_to_color_transform;
    std::mutex data_mutex;
    bool color_updated = false;
    bool depth_updated = false;
    std::unique_ptr<PointCloudViewer> viewer;
} global_data;

void signal_handler(int signal)
{
    std::cout << "\nReceived signal " << signal << ". Shutting down..." << std::endl;
    running = false;
    if (global_data.viewer)
    {
        global_data.viewer->shutdown();
    }
}

void receive_color_image(const sensor_msgs::CompressedImageConstPtr& msg)
{
    try
    {
        // Calculate image delay
        auto now = std::chrono::system_clock::now();
        auto now_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
        
        // Convert ROS timestamp to nanoseconds (sec + nsec)
        uint64_t msg_time_ns = (uint64_t)msg->header.stamp.sec * 1000000000ULL + (uint64_t)msg->header.stamp.nsec;
        
        // Calculate delay in milliseconds
        double delay_ms = (now_ns - msg_time_ns) / 1000000.0;
        
        std::cout << "[DEBUG] Color image delay: " << std::fixed << std::setprecision(1) 
                  << delay_ms << " ms (header: " << msg->header.stamp.sec << "." 
                  << std::setfill('0') << std::setw(9) << msg->header.stamp.nsec << ")" << std::endl;

        std::vector<uchar> img_data(msg->data.begin(), msg->data.end());
        cv::Mat image = cv::imdecode(img_data, cv::IMREAD_COLOR);

        if (!image.empty())
        {
            std::lock_guard<std::mutex> lock(global_data.data_mutex);
            global_data.latest_color_image = image.clone();
            global_data.color_updated = true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing color image: " << e.what() << std::endl;
    }
}

void receive_depth_image(const sensor_msgs::CompressedImageConstPtr& msg)
{
    try
    {
        cv::Mat depth_image;
        
        // Check the format field to determine how to decode
        if (msg->format.find("compressedDepth") != std::string::npos)
        {
            // This is a ROS compressedDepth format - need special handling
            if (msg->data.size() < 12) {
                std::cout << "[DEBUG] CompressedDepth data too small: " << msg->data.size() << " bytes" << std::endl;
                return;
            }
            
            // Skip the 12-byte header and look for PNG data
            const uint8_t* data = msg->data.data();
            size_t png_start = 12; // Skip the header
            
            // Look for PNG signature starting from after the header
            for (size_t i = 12; i < msg->data.size() - 8; i++) {
                if (data[i] == 0x89 && data[i+1] == 0x50 && data[i+2] == 0x4E && data[i+3] == 0x47 &&
                    data[i+4] == 0x0D && data[i+5] == 0x0A && data[i+6] == 0x1A && data[i+7] == 0x0A) {
                    png_start = i;
                    break;
                }
            }
            
            if (png_start >= msg->data.size()) {
                std::cout << "[DEBUG] No PNG signature found in compressedDepth data" << std::endl;
                return;
            }
            
            // Extract PNG data
            std::vector<uchar> png_data(msg->data.begin() + png_start, msg->data.end());
            depth_image = cv::imdecode(png_data, cv::IMREAD_ANYDEPTH);
        }
        else
        {
            // Regular compressed image (JPEG, PNG, etc.)
            std::vector<uchar> img_data(msg->data.begin(), msg->data.end());
            depth_image = cv::imdecode(img_data, cv::IMREAD_ANYDEPTH);
        }

        if (!depth_image.empty())
        {
            std::lock_guard<std::mutex> lock(global_data.data_mutex);
            global_data.latest_depth_image = depth_image.clone();
            global_data.depth_updated = true;
        }
        else
        {
            std::cout << "[DEBUG] Decompressed depth image is empty (format: " << msg->format << ")" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing depth image: " << e.what() << std::endl;
    }
}

void receive_camera_info(const sensor_msgs::CameraInfoConstPtr& msg)
{
    try
    {
        if (msg->K.size() >= 9)
        {
            double fx = msg->K[0];
            double fy = msg->K[4]; 
            double cx = msg->K[2];
            double cy = msg->K[5];
            int width = msg->width;
            int height = msg->height;

            std::lock_guard<std::mutex> lock(global_data.data_mutex);

            // Set up camera intrinsics
            global_data.color_intrinsics = CameraIntrinsics(fx, fy, cx, cy, width, height);
            global_data.depth_intrinsics = CameraIntrinsics(fx, fy, cx, cy, width, height);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing camera info: " << e.what() << std::endl;
    }
}

void receive_tf(const tf2_msgs::TFMessageConstPtr& msg)
{
    try
    {
        for (const auto& tf : msg->transforms)
        {
            std::string child_frame = tf.child_frame_id;

            // Look for depth to color camera transform
            if (child_frame.find("depth") != std::string::npos ||
                child_frame.find("color") != std::string::npos)
            {
                std::lock_guard<std::mutex> lock(global_data.data_mutex);

                global_data.depth_to_color_transform.translation[0] = tf.transform.translation.x;
                global_data.depth_to_color_transform.translation[1] = tf.transform.translation.y;
                global_data.depth_to_color_transform.translation[2] = tf.transform.translation.z;

                global_data.depth_to_color_transform.rotation[0] = tf.transform.rotation.x;
                global_data.depth_to_color_transform.rotation[1] = tf.transform.rotation.y;
                global_data.depth_to_color_transform.rotation[2] = tf.transform.rotation.z;
                global_data.depth_to_color_transform.rotation[3] = tf.transform.rotation.w;

                std::cout << "Updated transform for " << child_frame << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing tf: " << e.what() << std::endl;
    }
}

void update_point_cloud()
{
    std::lock_guard<std::mutex> lock(global_data.data_mutex);

    if (global_data.color_updated && global_data.depth_updated &&
        !global_data.latest_color_image.empty() && !global_data.latest_depth_image.empty())
    {

        // Generate point cloud
        auto points = generate_point_cloud(
            global_data.latest_color_image,
            global_data.latest_depth_image,
            global_data.color_intrinsics,
            global_data.depth_to_color_transform);

        if (global_data.viewer && !points.empty())
        {
            global_data.viewer->set_point_cloud(points);
        }

        global_data.color_updated = false;
        global_data.depth_updated = false;
    }
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

    std::cout << "Starting 3D Point Cloud Viewer..." << std::endl;

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
        miniros::init(remappings, "point_cloud_viewer");
    }
    else
    {
        miniros::init(argc, argv, "point_cloud_viewer");
    }

    // Initialize 3D viewer
    global_data.viewer = std::make_unique<PointCloudViewer>(1280, 720);
    if (!global_data.viewer->initialize())
    {
        std::cerr << "Failed to initialize 3D viewer" << std::endl;
        return 1;
    }

    // Set default camera intrinsics (these will be updated from camera_info)
    global_data.color_intrinsics = CameraIntrinsics(600, 600, 320, 240, 640, 480);
    global_data.depth_intrinsics = CameraIntrinsics(600, 600, 320, 240, 640, 480);

    // Create NodeHandle
    miniros::NodeHandle nh;

    // Create subscribers using miniros
    miniros::Subscriber color_sub = nh.subscribe("/camera/color/image_raw/compressed", 1, receive_color_image);
    miniros::Subscriber depth_sub = nh.subscribe("/camera/depth/image_rect_raw/compressedDepth", 1, receive_depth_image);
    miniros::Subscriber camera_info_sub = nh.subscribe("/camera/color/camera_info", 1, receive_camera_info);
    miniros::Subscriber tf_sub = nh.subscribe("/tf", 1, receive_tf);

    std::cout << "Subscribed to topics:" << std::endl;
    std::cout << "  - /camera/color/image_raw/compressed" << std::endl;
    std::cout << "  - /camera/depth/image_rect_raw/compressedDepth" << std::endl;
    std::cout << "  - /camera/color/camera_info" << std::endl;
    std::cout << "  - /tf" << std::endl;
    std::cout << "Waiting for messages..." << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  - Mouse: Rotate view" << std::endl;
    std::cout << "  - Scroll: Zoom in/out" << std::endl;
    std::cout << "  - R key: Reset view" << std::endl;
    std::cout << "  - ESC: Exit" << std::endl;

    // Main loop
    auto last_update = std::chrono::steady_clock::now();
    miniros::Rate rate(60); // 60 Hz
    
    while (running && miniros::ok() && !global_data.viewer->should_close())
    {
        // Process ROS callbacks
        miniros::spinOnce();

        // Update point cloud periodically
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update).count() > 100)
        {
            update_point_cloud();
            last_update = now;
        }

        // Update 3D viewer
        global_data.viewer->update();

        rate.sleep();
    }

    std::cout << "Shutting down..." << std::endl;

    // Clean up
    global_data.viewer->shutdown();
    miniros::shutdown();

    return 0;
}