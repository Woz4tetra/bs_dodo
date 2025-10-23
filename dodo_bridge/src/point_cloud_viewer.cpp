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
    float mean_x = 0.0f, mean_y = 0.0f;
    for (const auto& p : points) {
        mean_x += p.x;
        mean_y += p.y;
    }
    mean_x /= points.size();
    mean_y /= points.size();
    
    // Calculate standard deviation
    float var_x = 0.0f, var_y = 0.0f;
    for (const auto& p : points) {
        float dx = p.x - mean_x;
        float dy = p.y - mean_y;
        var_x += dx * dx;
        var_y += dy * dy;
    }
    var_x /= points.size();
    var_y /= points.size();
    
    float std_x = sqrt(var_x);
    float std_y = sqrt(var_y);
    
    // Set bounds using mean ± 2.5 * std_dev for stable visualization
    const float std_multiplier = 2.5f;
    float min_x = mean_x - std_multiplier * std_x;
    float max_x = mean_x + std_multiplier * std_x;
    float min_y = mean_y - std_multiplier * std_y;
    float max_y = mean_y + std_multiplier * std_y;
    
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



// Helper function to apply quaternion rotation
void apply_quaternion_rotation(float& x, float& y, float& z, const double q[4])
{
    // q = [x, y, z, w] quaternion
    float qx = q[0], qy = q[1], qz = q[2], qw = q[3];
    
    // Quaternion rotation: p' = q * p * q^-1
    // Optimized version for rotating a point
    float qx2 = qx * qx;
    float qy2 = qy * qy;
    float qz2 = qz * qz;
    float qxqy = qx * qy;
    float qxqz = qx * qz;
    float qxqw = qx * qw;
    float qyqz = qy * qz;
    float qyqw = qy * qw;
    float qzqw = qz * qw;
    
    float new_x = x * (1 - 2 * (qy2 + qz2)) + y * (2 * (qxqy - qzqw)) + z * (2 * (qxqz + qyqw));
    float new_y = x * (2 * (qxqy + qzqw)) + y * (1 - 2 * (qx2 + qz2)) + z * (2 * (qyqz - qxqw));
    float new_z = x * (2 * (qxqz - qyqw)) + y * (2 * (qyqz + qxqw)) + z * (1 - 2 * (qx2 + qy2));
    
    x = new_x;
    y = new_y;
    z = new_z;
}

// Utility functions
std::vector<Point3D> generate_point_cloud(
    const cv::Mat &color_image,
    const cv::Mat &depth_image,
    const CameraIntrinsics &color_intrinsics,
    const CameraIntrinsics &depth_intrinsics,
    const Transform &depth_to_color_transform,
    float depth_scale)
{
    std::vector<Point3D> points;

    if (color_image.empty() || depth_image.empty())
    {
        return points;
    }

    // Work with the original depth image size - don't resize it
    // We'll handle the coordinate mapping properly
    
    // Reserve space for efficiency
    points.reserve(depth_image.rows * depth_image.cols / 4); // Subsample for performance

    int step = 2; // Subsample every 2nd pixel for performance

    for (int v = 0; v < depth_image.rows; v += step)
    {
        for (int u = 0; u < depth_image.cols; u += step)
        {
            // Get depth value
            uint16_t depth_value = depth_image.at<uint16_t>(v, u);
            if (depth_value == 0)
                continue; // Skip invalid depth

            float depth = depth_value * depth_scale;
            if (depth > 10.0f)
                continue; // Skip points too far away

            // Convert depth pixel to 3D point in depth camera frame using depth intrinsics
            float x_depth = (u - depth_intrinsics.cx) * depth / depth_intrinsics.fx;
            float y_depth = (v - depth_intrinsics.cy) * depth / depth_intrinsics.fy;
            float z_depth = depth;

            // Apply depth-to-color transformation
            // First apply rotation
            apply_quaternion_rotation(x_depth, y_depth, z_depth, depth_to_color_transform.rotation);
            
            // Then apply translation
            float x_color = x_depth + depth_to_color_transform.translation[0];
            float y_color = y_depth + depth_to_color_transform.translation[1];
            float z_color = z_depth + depth_to_color_transform.translation[2];

            // Now project the transformed 3D point back to color image coordinates using color intrinsics
            if (z_color <= 0.001f) continue; // Skip points behind the camera
            
            float u_color = (x_color * color_intrinsics.fx / z_color) + color_intrinsics.cx;
            float v_color = (y_color * color_intrinsics.fy / z_color) + color_intrinsics.cy;
            
            // Check if the projected point is within the color image bounds
            int u_int = static_cast<int>(u_color + 0.5f);
            int v_int = static_cast<int>(v_color + 0.5f);
            
            if (u_int < 0 || u_int >= color_image.cols || v_int < 0 || v_int >= color_image.rows)
                continue; // Skip points outside color image

            // Get color from the projected coordinates
            cv::Vec3b color = color_image.at<cv::Vec3b>(v_int, u_int);
            float r = color[2] / 255.0f; // OpenCV uses BGR
            float g = color[1] / 255.0f;
            float b = color[0] / 255.0f;

            // Use the transformed 3D coordinates (in color camera frame)
            points.emplace_back(x_color, y_color, z_color, r, g, b);
        }
    }

    // Debug output for point cloud size
    if (points.empty()) {
        std::cout << "[DEBUG] No points generated in point cloud." << std::endl;
        std::cout << "[DEBUG] Color image size: " << color_image.cols << "x" << color_image.rows << std::endl;
        std::cout << "[DEBUG] Depth image size: " << depth_image.cols << "x" << depth_image.rows << std::endl;
        std::cout << "[DEBUG] Color intrinsics: fx=" << color_intrinsics.fx << ", fy=" << color_intrinsics.fy 
                  << ", cx=" << color_intrinsics.cx << ", cy=" << color_intrinsics.cy << std::endl;
        std::cout << "[DEBUG] Depth intrinsics: fx=" << depth_intrinsics.fx << ", fy=" << depth_intrinsics.fy 
                  << ", cx=" << depth_intrinsics.cx << ", cy=" << depth_intrinsics.cy << std::endl;
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