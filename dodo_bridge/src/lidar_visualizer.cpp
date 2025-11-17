#include <miniros/ros.h>
#include <sensor_msgs/LaserScan.hxx>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <map>
#include <string>
#include <mutex>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
#include <thread>

// Global flag for signal handling
volatile bool running = true;

// Global data for laser scan visualization
struct LaserScanData {
    std::vector<float> ranges;
    float angle_min;
    float angle_max;
    float angle_increment;
    float range_min;
    float range_max;
    uint32_t seq;
    double delay;
    std::chrono::system_clock::time_point receive_time;
    bool updated;
    
    LaserScanData() : updated(false) {}
};

struct VisualizerData {
    LaserScanData latest_scan;
    std::mutex data_mutex;
    
    // Display parameters
    int canvas_size = 800;
    int center = 400;
    float max_range = 10.0f;
    float scale_factor = 300.0f;
    
    // Performance tracking
    std::deque<double> delays;
    std::deque<std::chrono::system_clock::time_point> frame_times;
    
    // Colors (BGR format for OpenCV)
    cv::Scalar bg_color = cv::Scalar(20, 20, 20);
    cv::Scalar scan_color = cv::Scalar(0, 255, 0);  // Green
    cv::Scalar text_color = cv::Scalar(255, 255, 255);  // White
    cv::Scalar grid_color = cv::Scalar(50, 50, 50);  // Dark gray
} visualizer_data;

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
    std::cout << "Controls:" << std::endl;
    std::cout << "  q or ESC: Quit" << std::endl;
    std::cout << "  r: Reset statistics" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << program_name << " --master-uri http://192.168.1.100:11311 --ros-ip 192.168.1.50" << std::endl;
    std::cout << "  " << program_name << " --master-uri http://192.168.1.100:11311" << std::endl;
}

void receive_laser_scan(const sensor_msgs::LaserScanConstPtr& msg)
{
    try
    {
        auto now = std::chrono::system_clock::now();
        auto now_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
        
        // Convert ROS timestamp to nanoseconds
        uint64_t msg_time_ns = (uint64_t)msg->header.stamp.sec * 1000000000ULL + (uint64_t)msg->header.stamp.nsec;
        
        // Calculate delay in seconds
        double delay = (now_ns - msg_time_ns) / 1000000000.0;
        
        std::lock_guard<std::mutex> lock(visualizer_data.data_mutex);
        
        // Update scan data
        visualizer_data.latest_scan.ranges = msg->ranges;
        visualizer_data.latest_scan.angle_min = msg->angle_min;
        visualizer_data.latest_scan.angle_max = msg->angle_max;
        visualizer_data.latest_scan.angle_increment = msg->angle_increment;
        visualizer_data.latest_scan.range_min = msg->range_min;
        visualizer_data.latest_scan.range_max = msg->range_max;
        visualizer_data.latest_scan.seq = msg->header.seq;
        visualizer_data.latest_scan.delay = delay;
        visualizer_data.latest_scan.receive_time = now;
        visualizer_data.latest_scan.updated = true;
        
        // Update visualization parameters
        visualizer_data.max_range = std::min(msg->range_max, 2.0f);  // Cap at 2m
        visualizer_data.scale_factor = (visualizer_data.canvas_size * 0.4f) / visualizer_data.max_range;
        
        // Track performance
        visualizer_data.delays.push_back(delay);
        if (visualizer_data.delays.size() > 100) {
            visualizer_data.delays.pop_front();
        }
        
        std::cout << "[DEBUG] Laser scan seq=" << msg->header.seq 
                  << ", points=" << msg->ranges.size() 
                  << ", delay=" << std::fixed << std::setprecision(3) << delay << "s" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing laser scan: " << e.what() << std::endl;
    }
}

void draw_grid(cv::Mat& canvas)
{
    // Draw range circles
    for (int r = 1; r <= (int)visualizer_data.max_range; r++) {
        int radius = (int)(r * visualizer_data.scale_factor);
        if (radius < visualizer_data.canvas_size / 2) {
            cv::circle(canvas, cv::Point(visualizer_data.center, visualizer_data.center), 
                      radius, visualizer_data.grid_color, 1);
            
            // Add range labels
            std::string text = std::to_string(r) + "m";
            int baseline;
            cv::Size text_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.4, 1, &baseline);
            cv::putText(canvas, text,
                       cv::Point(visualizer_data.center + radius - text_size.width/2, 
                                visualizer_data.center - 5),
                       cv::FONT_HERSHEY_SIMPLEX, 0.4, visualizer_data.grid_color, 1);
        }
    }
    
    // Draw angle lines (every 30 degrees)
    for (int angle_deg = 0; angle_deg < 360; angle_deg += 30) {
        float angle_rad = angle_deg * M_PI / 180.0f;
        int end_x = (int)(visualizer_data.center + (visualizer_data.canvas_size / 2) * cos(angle_rad));
        int end_y = (int)(visualizer_data.center + (visualizer_data.canvas_size / 2) * sin(angle_rad));
        cv::line(canvas, cv::Point(visualizer_data.center, visualizer_data.center), 
                cv::Point(end_x, end_y), visualizer_data.grid_color, 1);
    }
}

void draw_scan_data(cv::Mat& canvas, const LaserScanData& scan_data)
{
    std::vector<cv::Point> points;
    
    for (size_t i = 0; i < scan_data.ranges.size(); i++) {
        float range_val = scan_data.ranges[i];
        
        if (!std::isinf(range_val) && !std::isnan(range_val) && 
            range_val >= scan_data.range_min && range_val <= scan_data.range_max) {
            
            // Calculate angle
            float angle = scan_data.angle_min + i * scan_data.angle_increment;
            
            // Convert to screen coordinates (rotate by -90 degrees to make forward direction up)
            float screen_angle = angle - M_PI/2;
            
            // Scale range to pixels
            float scaled_range = range_val * visualizer_data.scale_factor;
            
            int x = (int)(visualizer_data.center + scaled_range * cos(screen_angle));
            int y = (int)(visualizer_data.center + scaled_range * sin(screen_angle));
            
            // Check bounds
            if (x >= 0 && x < visualizer_data.canvas_size && 
                y >= 0 && y < visualizer_data.canvas_size) {
                points.push_back(cv::Point(x, y));
            }
        }
    }
    
    // Draw scan points
    for (const auto& point : points) {
        cv::circle(canvas, point, 2, visualizer_data.scan_color, -1);
    }
    
    // Draw connecting lines for better visualization
    if (points.size() > 1) {
        for (size_t i = 0; i < points.size() - 1; i++) {
            // Only connect nearby points to avoid long lines across obstacles
            float dist = sqrt(pow(points[i+1].x - points[i].x, 2) + pow(points[i+1].y - points[i].y, 2));
            if (dist < 20) {  // pixels
                cv::line(canvas, points[i], points[i+1], visualizer_data.scan_color, 1);
            }
        }
    }
}

void draw_stats(cv::Mat& canvas, const LaserScanData& scan_data)
{
    auto current_time = std::chrono::system_clock::now();
    visualizer_data.frame_times.push_back(current_time);
    if (visualizer_data.frame_times.size() > 100) {
        visualizer_data.frame_times.pop_front();
    }
    
    // Calculate FPS
    float fps = 0.0f;
    if (visualizer_data.frame_times.size() > 1) {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            visualizer_data.frame_times.back() - visualizer_data.frame_times.front()).count();
        if (duration > 0) {
            fps = (visualizer_data.frame_times.size() - 1) * 1000.0f / duration;
        }
    }
    
    // Calculate average delay
    double avg_delay = 0.0;
    double max_delay = 0.0;
    if (!visualizer_data.delays.empty()) {
        for (double d : visualizer_data.delays) {
            avg_delay += d;
            max_delay = std::max(max_delay, d);
        }
        avg_delay /= visualizer_data.delays.size();
    }
    
    // Prepare stats
    std::vector<std::string> stats = {
        "Seq: " + std::to_string(scan_data.seq),
        "Points: " + std::to_string(scan_data.ranges.size()),
        "Current Delay: " + std::to_string(scan_data.delay).substr(0, 5) + "s",
        "Avg Delay: " + std::to_string(avg_delay).substr(0, 5) + "s",
        "Max Delay: " + std::to_string(max_delay).substr(0, 5) + "s",
        "Display FPS: " + std::to_string(fps).substr(0, 4),
        "Range: " + std::to_string(visualizer_data.max_range).substr(0, 4) + "m"
    };
    
    // Draw stats text
    int y_offset = 20;
    for (size_t i = 0; i < stats.size(); i++) {
        cv::Scalar color = visualizer_data.text_color;
        // Highlight high delays in red
        if (stats[i].find("Delay:") != std::string::npos && scan_data.delay > 0.1) {
            color = cv::Scalar(0, 0, 255);  // Red for high delay
        }
        
        cv::putText(canvas, stats[i], cv::Point(10, y_offset + i * 25),
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, color, 2);
    }
    
    // Draw center crosshair
    cv::line(canvas, cv::Point(visualizer_data.center - 10, visualizer_data.center),
            cv::Point(visualizer_data.center + 10, visualizer_data.center),
            visualizer_data.text_color, 2);
    cv::line(canvas, cv::Point(visualizer_data.center, visualizer_data.center - 10),
            cv::Point(visualizer_data.center, visualizer_data.center + 10),
            visualizer_data.text_color, 2);
}

void run_visualization()
{
    const std::string window_name = "LIDAR Scan Visualization";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    
    std::cout << "Starting visualization loop. Press 'q' or ESC to quit, 'r' to reset stats." << std::endl;
    
    while (running) {
        // Create blank canvas
        cv::Mat canvas(visualizer_data.canvas_size, visualizer_data.canvas_size, CV_8UC3, visualizer_data.bg_color);
        
        // Draw grid
        draw_grid(canvas);
        
        // Get latest scan data
        LaserScanData scan_data;
        bool has_data = false;
        {
            std::lock_guard<std::mutex> lock(visualizer_data.data_mutex);
            if (visualizer_data.latest_scan.updated) {
                scan_data = visualizer_data.latest_scan;
                has_data = true;
            }
        }
        
        if (has_data) {
            // Draw scan data
            draw_scan_data(canvas, scan_data);
            
            // Draw statistics
            draw_stats(canvas, scan_data);
        } else {
            // No data received yet
            cv::putText(canvas, "Waiting for LIDAR data...",
                       cv::Point(visualizer_data.center - 100, visualizer_data.center),
                       cv::FONT_HERSHEY_SIMPLEX, 0.8, visualizer_data.text_color, 2);
        }
        
        // Display canvas
        cv::imshow(window_name, canvas);
        
        // Handle key presses
        int key = cv::waitKey(1) & 0xFF;
        if (key == 'q' || key == 27) {  // 'q' or ESC
            running = false;
            break;
        } else if (key == 'r') {  // Reset statistics
            std::lock_guard<std::mutex> lock(visualizer_data.data_mutex);
            visualizer_data.frame_times.clear();
            visualizer_data.delays.clear();
            std::cout << "Statistics reset" << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~60 FPS
    }
    
    cv::destroyAllWindows();
    std::cout << "Visualization stopped" << std::endl;
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

    std::cout << "Starting LIDAR Scan Visualizer..." << std::endl;

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
        miniros::init(remappings, "lidar_visualizer");
    }
    else
    {
        miniros::init(argc, argv, "lidar_visualizer");
    }

    // Create NodeHandle
    miniros::NodeHandle nh;

    // Create subscriber for laser scan
    miniros::Subscriber laser_sub = nh.subscribe("/laser/scan", 1, receive_laser_scan);

    std::cout << "Subscribed to /laser/scan topic" << std::endl;
    std::cout << "Waiting for laser scan messages..." << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  - q or ESC: Exit" << std::endl;
    std::cout << "  - r: Reset statistics" << std::endl;

    // Start visualization in a separate thread while ROS spins
    std::thread viz_thread(run_visualization);

    // Main ROS loop
    miniros::Rate rate(100);  // 100 Hz for responsive message processing
    while (running && miniros::ok()) {
        miniros::spinOnce();
        rate.sleep();
    }

    // Wait for visualization thread to finish
    viz_thread.join();

    std::cout << "Shutting down..." << std::endl;
    miniros::shutdown();

    return 0;
}