#include "point_cloud_viewer.h"
#include <iostream>
#include <cmath>
#include <algorithm>

PointCloudViewer::PointCloudViewer(int width, int height)
    : width_(width), height_(height),
      points_updated_(false), should_close_(false),
      camera_yaw_(0.0f), camera_pitch_(0.0f), camera_distance_(1.0f)
{
}

PointCloudViewer::~PointCloudViewer()
{
    shutdown();
}

bool PointCloudViewer::initialize()
{
    std::cout << "Point Cloud Viewer initialized successfully" << std::endl;
    return true;
}

void PointCloudViewer::shutdown()
{
    should_close_ = true;
    cv::destroyAllWindows();
}

bool PointCloudViewer::should_close()
{
    return should_close_;
}

void PointCloudViewer::update()
{
    if (should_close_)
        return;

    // Update point cloud visualization if needed
    {
        std::lock_guard<std::mutex> lock(points_mutex_);
        if (points_updated_ && !points_.empty())
        {
            update_display();
            points_updated_ = false;
        }
    }

    // Handle keyboard input
    int key = cv::waitKey(1) & 0xFF;
    if (key == 27 || key == 'q') { // ESC or 'q' to quit
        should_close_ = true;
    }
    else if (key == 'w') {
        camera_pitch_ -= 0.1f;
    }
    else if (key == 's') {
        camera_pitch_ += 0.1f;
    }
    else if (key == 'a') {
        camera_yaw_ -= 0.1f;
    }
    else if (key == 'd') {
        camera_yaw_ += 0.1f;
    }
    else if (key == 'r') {
        // Reset camera
        camera_yaw_ = camera_pitch_ = 0.0f;
        camera_distance_ = 1.0f;
    }
}

void PointCloudViewer::set_point_cloud(const std::vector<Point3D> &points)
{
    std::lock_guard<std::mutex> lock(points_mutex_);
    points_ = points;
    points_updated_ = true;
}

void PointCloudViewer::update_display()
{
    if (points_.empty())
        return;
        
    cv::Mat display_image = project_points_to_2d(points_);
    
    // Add control instructions
    cv::putText(display_image, "Controls: WASD=rotate, R=reset, Q/ESC=quit", 
                cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
    
    cv::imshow("Point Cloud Viewer", display_image);
}

cv::Mat PointCloudViewer::project_points_to_2d(const std::vector<Point3D>& points)
{
    cv::Mat image = cv::Mat::zeros(height_, width_, CV_8UC3);
    
    if (points.empty())
        return image;
    
    // Calculate mean position
    float mean_x = 0.0f, mean_y = 0.0f, mean_z = 0.0f;
    for (const auto& p : points) {
        mean_x += p.x;
        mean_y += p.y;
        mean_z += p.z;
    }
    mean_x /= points.size();
    mean_y /= points.size();
    mean_z /= points.size();
    
    // Calculate standard deviation
    float var_x = 0.0f, var_y = 0.0f, var_z = 0.0f;
    for (const auto& p : points) {
        float dx = p.x - mean_x;
        float dy = p.y - mean_y;
        float dz = p.z - mean_z;
        var_x += dx * dx;
        var_y += dy * dy;
        var_z += dz * dz;
    }
    var_x /= points.size();
    var_y /= points.size();
    var_z /= points.size();
    
    float std_x = sqrt(var_x);
    float std_y = sqrt(var_y);
    float std_z = sqrt(var_z);
    
    // Set bounds using mean ± 2.5 * std_dev for stable visualization
    const float std_multiplier = 2.5f;
    float min_x = mean_x - std_multiplier * std_x;
    float max_x = mean_x + std_multiplier * std_x;
    float min_y = mean_y - std_multiplier * std_y;
    float max_y = mean_y + std_multiplier * std_y;
    float min_z = mean_z - std_multiplier * std_z;
    float max_z = mean_z + std_multiplier * std_z;
    
    // Ensure we have some minimum range to avoid division by zero
    if (max_x - min_x < 1e-6f) {
        min_x -= 0.1f;
        max_x += 0.1f;
    }
    if (max_y - min_y < 1e-6f) {
        min_y -= 0.1f;
        max_y += 0.1f;
    }
    
    // Apply camera rotation
    float cos_yaw = cos(camera_yaw_), sin_yaw = sin(camera_yaw_);
    float cos_pitch = cos(camera_pitch_), sin_pitch = sin(camera_pitch_);
    
    // Project 3D points to 2D
    for (const auto& point : points) {
        // Apply rotation
        float x = point.x;
        float y = point.y * cos_pitch - point.z * sin_pitch;
        float z = point.y * sin_pitch + point.z * cos_pitch;
        
        float rotated_x = x * cos_yaw + z * sin_yaw;
        float rotated_z = -x * sin_yaw + z * cos_yaw;
        
        // Simple orthographic projection (ignore rotated_z for depth)
        // Map to screen coordinates
        int screen_x = static_cast<int>((rotated_x - min_x) / (max_x - min_x) * (width_ - 40) + 20);
        int screen_y = static_cast<int>((y - min_y) / (max_y - min_y) * (height_ - 40) + 20);
        
        // Clamp to image bounds
        screen_x = std::max(0, std::min(width_ - 1, screen_x));
        screen_y = std::max(0, std::min(height_ - 1, screen_y));
        
        // Set pixel color (OpenCV uses BGR)
        cv::Vec3b color(
            static_cast<uchar>(point.b * 255),
            static_cast<uchar>(point.g * 255),
            static_cast<uchar>(point.r * 255)
        );
        
        // Draw a small circle for each point
        cv::circle(image, cv::Point(screen_x, screen_y), 1, color, -1);
    }
    
    return image;
}



// Utility functions
std::vector<Point3D> generate_point_cloud(
    const cv::Mat &color_image,
    const cv::Mat &depth_image,
    const CameraIntrinsics &intrinsics,
    const Transform &depth_to_color_transform,
    float depth_scale)
{
    std::vector<Point3D> points;

    if (color_image.empty() || depth_image.empty())
    {
        return points;
    }

    // Ensure images are the same size (depth aligned to color)
    cv::Mat aligned_depth;
    if (depth_image.size() != color_image.size())
    {
        cv::resize(depth_image, aligned_depth, color_image.size());
    }
    else
    {
        aligned_depth = depth_image;
    }

    // Reserve space for efficiency
    points.reserve(color_image.rows * color_image.cols / 4); // Subsample for performance

    int step = 2; // Subsample every 2nd pixel for performance

    float min_x = FLT_MAX, max_x = -FLT_MAX;
    float min_y = FLT_MAX, max_y = -FLT_MAX;
    float min_z = FLT_MAX, max_z = -FLT_MAX;

    for (int v = 0; v < color_image.rows; v += step)
    {
        for (int u = 0; u < color_image.cols; u += step)
        {
            // Get depth value
            uint16_t depth_value = aligned_depth.at<uint16_t>(v, u);
            if (depth_value == 0)
                continue; // Skip invalid depth

            float depth = depth_value * depth_scale;
            if (depth > 10.0f)
                continue; // Skip points too far away

            // Convert pixel to 3D point
            float x = (u - intrinsics.cx) * depth / intrinsics.fx;
            float y = (v - intrinsics.cy) * depth / intrinsics.fy;
            float z = depth;

            // Apply depth-to-color transformation (simplified - just translation for now)
            x += depth_to_color_transform.translation[0];
            y += depth_to_color_transform.translation[1];
            z += depth_to_color_transform.translation[2];

            // Track bounds for debugging
            min_x = std::min(min_x, x); max_x = std::max(max_x, x);
            min_y = std::min(min_y, y); max_y = std::max(max_y, y);
            min_z = std::min(min_z, z); max_z = std::max(max_z, z);

            // Get color
            cv::Vec3b color = color_image.at<cv::Vec3b>(v, u);
            float r = color[2] / 255.0f; // OpenCV uses BGR
            float g = color[1] / 255.0f;
            float b = color[0] / 255.0f;

            points.emplace_back(x, y, z, r, g, b);
        }
    }

    // Debug output for point cloud bounds
    if (points.empty()) {
        std::cout << "[DEBUG] No points generated in point cloud." << std::endl;
    }

    return points;
}

cv::Mat decompress_depth_image(const std::string &compressed_data)
{
    // This function is now deprecated - kept for compatibility
    // The main processing now handles native ROS CompressedImage messages directly
    std::cerr << "Warning: decompress_depth_image() called with string data - this is deprecated" << std::endl;
    
    // Try to decode directly as image data
    std::vector<uchar> img_data(compressed_data.begin(), compressed_data.end());
    cv::Mat depth_image = cv::imdecode(img_data, cv::IMREAD_ANYDEPTH);
    
    return depth_image;
}