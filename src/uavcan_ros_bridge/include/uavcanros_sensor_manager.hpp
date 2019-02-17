#pragma once

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

#include <ros/ros.h>
#include "uavcan_sensor_manager.hpp"
#include "seven_robotics_msgs/AdisImu.h"

class UavcanRosSensorManager : public UavcanSensorManager
{
	private:
		static const unsigned MemoryBlockPoolSize=16384;
		using Node=uavcan::Node<MemoryBlockPoolSize>;
		ros::NodeHandle& _nh;

	public:
		ros::Publisher  imu_pub;

		UavcanRosSensorManager(Node& node,ros::NodeHandle& nh):
						UavcanSensorManager(node),
						_nh{nh}
		{
			ROS_INFO("Initializing Sensor Manager\n");
			imu_pub = _nh.advertise<seven_robotics_msgs::AdisImu>("Adis",100);

			ROS_INFO("Started IMU Sensor publisher, publishing on %s",imu_pub.getTopic().c_str());
		}

		virtual void imu_cb(const uavcan::ReceivedDataStructure<uavcan::equipment::imu::AdisImu>& msg) noexcept override;
};

