#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <map>
#include <miniros/ros.h>
#include <chrono>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <db_parsing/DodobotSetState.hxx>
#include <db_parsing/DodobotTilter.hxx>
#include <sensor_msgs/CompressedImage.hxx>
#include <std_msgs/Header.hxx>


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
            std::cout<<"\nyay";
            cv::namedWindow("Display Window", cv::WINDOW_AUTOSIZE);
            cv::imshow("Display Window", image);
            cv::waitKey(1);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing color image: " << e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    const std::string NODE_NAME = "detect_cube";

    // TODO move to config
    const std::string ROS_MASTER_URI = "http://192.168.50.169:11311";
    std::cout << "Using ROS Master URI: " << ROS_MASTER_URI << std::endl;
    setenv("ROS_MASTER_URI", ROS_MASTER_URI.c_str(), 1);
    
    const std::string ROS_IP = "192.168.50.212";
    std::cout << "Using ROS IP: " << ROS_IP << std::endl;
    setenv("ROS_IP", ROS_IP.c_str(), 1);

    // Initialize miniros with remapping support
    std::map<std::string, std::string> remappings;
    remappings["__master"] = ROS_MASTER_URI;
    miniros::init(remappings, NODE_NAME);
    
    miniros::NodeHandle nh;
    miniros::Subscriber color_sub = nh.subscribe("/camera/color/image_raw_throttled/compressed", 1, receive_color_image);

    miniros::ServiceClient client = nh.serviceClient<db_parsing::DodobotSetState>("/dodobot/set_state");
    db_parsing::DodobotSetState foo;
    foo.reporting = true;
    foo.active = true;
    bool result = client.call(foo);
    std::cout << "Motor enable succeeded: " << result << std::endl;

    miniros::Publisher tilt_pub = nh.advertise<db_parsing::DodobotTilter>("/dodobot/tilter_cmd", 10, true);
    std_msgs::Header header;
    db_parsing::DodobotTilter bar;
    bar.position = 0;
    bar.command = 0;
    bar.header = header;
    tilt_pub.publish(bar);
    std::cout << "published tilt message: " << bar << std::endl ;

    miniros::Rate rate(240); // Hz
    while (miniros::ok())
    {
        miniros::spinOnce();
        rate.sleep();
    }


    std::cout << "Shutting down..." << std::endl;
    cv::destroyAllWindows();
    miniros::shutdown();

    return 0;
}