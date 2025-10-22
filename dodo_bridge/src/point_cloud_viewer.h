#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include <mutex>

struct Point3D
{
    float x, y, z;
    float r, g, b;

    Point3D(float x_, float y_, float z_, float r_, float g_, float b_)
        : x(x_), y(y_), z(z_), r(r_), g(g_), b(b_) {}
};

class PointCloudViewer
{
public:
    PointCloudViewer(int width = 1280, int height = 720);
    ~PointCloudViewer();

    bool initialize();
    void shutdown();
    bool should_close();
    void update();
    void set_point_cloud(const std::vector<Point3D> &points);

private:
    int width_, height_;
    
    // Point cloud data
    std::vector<Point3D> points_;
    std::mutex points_mutex_;
    bool points_updated_;
    bool should_close_;
    
    // Visualization parameters
    float camera_yaw_;
    float camera_pitch_;
    float camera_distance_;
    
    // Create 2D projection of 3D point cloud
    void update_display();
    cv::Mat project_points_to_2d(const std::vector<Point3D>& points);
};

// Camera intrinsic parameters structure
struct CameraIntrinsics
{
    double fx, fy, cx, cy;
    int width, height;

    CameraIntrinsics() : fx(0), fy(0), cx(0), cy(0), width(0), height(0) {}
    CameraIntrinsics(double fx_, double fy_, double cx_, double cy_, int w, int h)
        : fx(fx_), fy(fy_), cx(cx_), cy(cy_), width(w), height(h) {}
};

// Transform structure for camera poses
struct Transform
{
    double translation[3]; // x, y, z
    double rotation[4];    // quaternion: x, y, z, w

    Transform()
    {
        translation[0] = translation[1] = translation[2] = 0.0;
        rotation[0] = rotation[1] = rotation[2] = 0.0;
        rotation[3] = 1.0; // identity quaternion
    }
};

// Helper function for quaternion rotation
void apply_quaternion_rotation(float& x, float& y, float& z, const double q[4]);

// Point cloud generation utilities
std::vector<Point3D> generate_point_cloud(
    const cv::Mat &color_image,
    const cv::Mat &depth_image,
    const CameraIntrinsics &color_intrinsics,
    const CameraIntrinsics &depth_intrinsics,
    const Transform &depth_to_color_transform,
    float depth_scale = 0.001f // Convert depth units to meters
);

cv::Mat decompress_depth_image(const std::string &compressed_data);