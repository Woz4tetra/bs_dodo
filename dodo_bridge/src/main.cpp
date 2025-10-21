#include "ros_client.h"
#include "topic_subscriber.h"
#include "point_cloud_viewer.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <signal.h>
#include <iomanip>
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

void receive_color_image(const Json::Value &msg)
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    if (msg.isMember("data"))
    {
        try
        {
            std::string base64_data = msg["data"].asString();

            // Decode base64 to binary
            std::string binary_data;
            const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            int val = 0, valb = -8;
            for (unsigned char c : base64_data)
            {
                if (chars.find(c) == std::string::npos)
                    break;
                val = (val << 6) + chars.find(c);
                valb += 6;
                if (valb >= 0)
                {
                    binary_data.push_back(char((val >> valb) & 0xFF));
                    valb -= 8;
                }
            }

            std::vector<uchar> img_data(binary_data.begin(), binary_data.end());
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
}

void receive_depth_image(const Json::Value &msg)
{
    if (msg.isMember("data"))
    {
        try
        {
            std::string base64_data = msg["data"].asString();

            cv::Mat depth_image = decompress_depth_image(base64_data);

            if (!depth_image.empty())
            {
                std::lock_guard<std::mutex> lock(global_data.data_mutex);
                global_data.latest_depth_image = depth_image.clone();
                global_data.depth_updated = true;
            }
            else
            {
                std::cout << "[DEBUG] Decompressed depth image is empty" << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing depth image: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "[DEBUG] Message does not have 'data' field" << std::endl;
    }
}

void receive_camera_info(const Json::Value &msg)
{
    if (msg.isMember("K") && msg.isMember("width") && msg.isMember("height"))
    {
        try
        {
            const Json::Value &K = msg["K"];
            if (K.isArray() && K.size() >= 9)
            {
                double fx = K[0].asDouble();
                double fy = K[4].asDouble();
                double cx = K[2].asDouble();
                double cy = K[5].asDouble();
                int width = msg["width"].asInt();
                int height = msg["height"].asInt();

                std::lock_guard<std::mutex> lock(global_data.data_mutex);

                // Determine if this is color or depth camera info based on topic
                // We'll set up default intrinsics for now
                global_data.color_intrinsics = CameraIntrinsics(fx, fy, cx, cy, width, height);
                global_data.depth_intrinsics = CameraIntrinsics(fx, fy, cx, cy, width, height);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing camera info: " << e.what() << std::endl;
        }
    }
}

void receive_tf(const Json::Value &msg)
{
    if (msg.isMember("transforms") && msg["transforms"].isArray())
    {
        try
        {
            const Json::Value &transforms = msg["transforms"];
            for (const Json::Value &tf : transforms)
            {
                if (tf.isMember("child_frame_id") && tf.isMember("transform"))
                {
                    std::string child_frame = tf["child_frame_id"].asString();

                    // Look for depth to color camera transform
                    if (child_frame.find("depth") != std::string::npos ||
                        child_frame.find("color") != std::string::npos)
                    {

                        const Json::Value &transform = tf["transform"];
                        if (transform.isMember("translation") && transform.isMember("rotation"))
                        {
                            std::lock_guard<std::mutex> lock(global_data.data_mutex);

                            const Json::Value &trans = transform["translation"];
                            global_data.depth_to_color_transform.translation[0] = trans["x"].asDouble();
                            global_data.depth_to_color_transform.translation[1] = trans["y"].asDouble();
                            global_data.depth_to_color_transform.translation[2] = trans["z"].asDouble();

                            const Json::Value &rot = transform["rotation"];
                            global_data.depth_to_color_transform.rotation[0] = rot["x"].asDouble();
                            global_data.depth_to_color_transform.rotation[1] = rot["y"].asDouble();
                            global_data.depth_to_color_transform.rotation[2] = rot["z"].asDouble();
                            global_data.depth_to_color_transform.rotation[3] = rot["w"].asDouble();

                            std::cout << "Updated transform for " << child_frame << std::endl;
                        }
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing tf: " << e.what() << std::endl;
        }
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

int main()
{
    // Set up signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::cout << "Starting 3D Point Cloud Viewer..." << std::endl;

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

    // Create ROS client
    RosClient client("192.168.50.169", 9090);

    // Connect to ROSBridge
    if (!client.connect())
    {
        std::cerr << "Failed to connect to ROSBridge server" << std::endl;
        return 1;
    }

    // Start the client
    client.run();

    // Wait for connection
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    if (!client.is_connected())
    {
        std::cerr << "Failed to establish connection to ROSBridge server" << std::endl;
        return 1;
    }

    std::cout << "Connected to ROSBridge server" << std::endl;

    // Create topic subscribers
    TopicSubscriber color_subscriber(client, "/camera/color/image_raw/compressed", "sensor_msgs/CompressedImage");
    TopicSubscriber depth_subscriber(client, "/camera/depth/image_rect_raw/compressedDepth", "sensor_msgs/CompressedImage");
    TopicSubscriber camera_info_subscriber(client, "/camera/color/camera_info", "sensor_msgs/CameraInfo");
    TopicSubscriber tf_subscriber(client, "/tf", "tf2_msgs/TFMessage");

    // Subscribe to topics
    color_subscriber.subscribe(receive_color_image);
    depth_subscriber.subscribe(receive_depth_image);
    camera_info_subscriber.subscribe(receive_camera_info);
    tf_subscriber.subscribe(receive_tf);

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
    while (running && client.is_connected() && !global_data.viewer->should_close())
    {
        // Update point cloud periodically
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update).count() > 100)
        {
            update_point_cloud();
            last_update = now;
        }

        // Update 3D viewer
        global_data.viewer->update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    std::cout << "Shutting down..." << std::endl;

    // Clean up
    color_subscriber.unsubscribe();
    depth_subscriber.unsubscribe();
    camera_info_subscriber.unsubscribe();
    tf_subscriber.unsubscribe();

    client.stop();
    global_data.viewer->shutdown();

    return 0;
}