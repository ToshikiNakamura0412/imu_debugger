#include "imu_debugger/imu_debugger.h"

IMUDebugger::IMUDebugger():private_nh_("~")
{
    private_nh_.param("hz", hz_, {200});
    imu_data_.header.frame_id = "imu";
    imu_sub_ = nh_.subscribe("/imu/data", 1, &IMUDebugger::imu_callback, this);
    imu_pub_ = nh_.advertise<sensor_msgs::Imu>("/imu/fixed_data", 1);
}

void IMUDebugger::imu_callback(const sensor_msgs::Imu::ConstPtr& msg)
{
    imu_data_ = *msg;
    try
    {
        const geometry_msgs::TransformStamped trans = tf_buffer_.lookupTransform("base_link", "imu", ros::Time(0));
        /* tf2::doTransform(*msg, imu_data_, trans); */
    }
    catch(tf2::TransformException& ex)
    {
        ROS_WARN("%s", ex.what());
        return;
    }

    imu_data_.linear_acceleration.x *= 9.80665;
    imu_data_.linear_acceleration.y *= 9.80665;
    imu_data_.linear_acceleration.z *= 9.80665;
    imu_pub_.publish(imu_data_);
}

void IMUDebugger::process()
{
    ros::Rate loop_rate(hz_);
    tf2_ros::TransformListener tf_listener(tf_buffer_);
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "imu_debugger");
    IMUDebugger debugger;
    debugger.process();
    return 0;
}
