#pragma once

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <uavcan/uavcan.hpp>
#include <uavcan/equipment/imu/AdisImu.hpp>


class UavcanSensorManager {
private:
	const static unsigned MemoryBlockPoolSize=16384;
	using Node=uavcan::Node<MemoryBlockPoolSize>;

public:
	uavcan::Subscriber<uavcan::equipment::imu::AdisImu> imu_sub;
	uavcan::equipment::imu::AdisImu imu_msg;
	
	UavcanSensorManager(Node& node):
	imu_sub(node)
	{
		const int sub_res = imu_sub.start([&](const uavcan::ReceivedDataStructure<uavcan::equipment::imu::AdisImu>& msg){
										this->imu_cb(msg);});
	}

	virtual void imu_cb(const uavcan::ReceivedDataStructure<uavcan::equipment::imu::AdisImu>& msg) noexcept=0;
};
