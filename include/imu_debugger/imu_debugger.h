#ifndef IMU_DEBUGGER
#define IMU_DEBUGGER

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <tf2_ros/transform_listener.h>
#include <../../imu_pipeline/imu_transformer/include/imu_transformer/tf2_sensor_msgs.h>
/* #include <drive_ros_msgs/tf2_IMU.h> */

class IMUDebugger
{
public:
    IMUDebugger();
    void process();

private:
    void imu_callback(const sensor_msgs::Imu::ConstPtr& msg);

    int hz_;

    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;
    ros::Subscriber imu_sub_;
    ros::Publisher  imu_pub_;
    sensor_msgs::Imu imu_data_;
    tf2_ros::Buffer tf_buffer_;
};

#endif
