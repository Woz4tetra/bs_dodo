#include "generated_include/db_parsing/DodobotNotify.hxx"
#include "generated_include/sensor_msgs/LaserScan.hxx"
#include <iostream>

int main() {
    db_parsing::DodobotNotify notify_msg;
    notify_msg.message = "Test message";
    notify_msg.level = db_parsing::DodobotNotify::WARN;
    notify_msg.timeout = 5000;
    
    sensor_msgs::LaserScan scan_msg;
    scan_msg.angle_min = -1.57f;
    scan_msg.angle_max = 1.57f;
    scan_msg.ranges.push_back(1.0f);
    scan_msg.ranges.push_back(2.0f);
    
    std::cout << "DodobotNotify message: " << notify_msg.message << std::endl;
    std::cout << "Level: " << notify_msg.level << " (WARN=" << db_parsing::DodobotNotify::WARN << ")" << std::endl;
    std::cout << "LaserScan angle range: " << scan_msg.angle_min << " to " << scan_msg.angle_max << std::endl;
    std::cout << "Ranges count: " << scan_msg.ranges.size() << std::endl;
    
    return 0;
}