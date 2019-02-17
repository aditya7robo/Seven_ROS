#include "uavcanros_sensor_manager.hpp"

void UavcanRosSensorManager::imu_cb(const uavcan::ReceivedDataStructure<uavcan::equipment::imu::AdisImu>& msg) noexcept
{
	seven_robotics_msgs::AdisImu ros_msg;
	
	ros_msg.header.stamp = ros::Time::now();
	ros_msg.gyro_latest[0] = msg.gyro_latest[0];
	ros_msg.gyro_latest[1] = msg.gyro_latest[1];
	ros_msg.gyro_latest[2] = msg.gyro_latest[2];
	ros_msg.accel_latest[0] = msg.accel_latest[0];
	ros_msg.accel_latest[1] = msg.accel_latest[1];
	ros_msg.accel_latest[2] = msg.accel_latest[2];

	imu_pub.publish(ros_msg);
}
