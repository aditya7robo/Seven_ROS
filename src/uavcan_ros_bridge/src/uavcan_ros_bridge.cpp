#include <iostream>
#include <cstdint>


#include <uavcan/uavcan.hpp>

#include<ros/ros.h>

#include "uavcanros_sensor_manager.hpp"

extern uavcan::ICanDriver& getCanDriver();
extern uavcan::ISystemClock& getSystemClock();

class UavcanRosBridge
{
	static const uint32_t MemoryBlockPoolSize = 16384;
	using Node = uavcan::Node<MemoryBlockPoolSize>;

	public:

	int node_id;
	ros::NodeHandle bridge_nh;
	Node node;
	UavcanRosSensorManager sensor_mgr;

	UavcanRosBridge(int id):
			node_id{id},
			node(getCanDriver(),getSystemClock()),
			sensor_mgr(node,bridge_nh)
	{
		node.setNodeID(node_id);
		node.setName("adis.imu.subscriber");

		const int node_res = node.start();
		if(node_res < 0)
		{
			std::cerr << "Failed to start UAVCAN Node\r\n";
		}

		node.setModeOperational();
	}

	void spin(){
		while(ros::ok())	{
			ros::spinOnce();
			const int res = node.spin(uavcan::MonotonicDuration::fromMSec(10));
			if(res < 0)
						std::cerr << "uavcan bridge spin error\n";
		}
	}
};

int main(int argc,char** argv)
{
 	if(argc < 2)
	{
		std::cerr << "Usage: "<<argv[0]<< " <uavcan-id>" << std::endl;
		return 1;
	}

	ros::init(argc,argv,"uavcanRosNode");
	UavcanRosBridge bridge(std::stoi(argv[1]));
	bridge.spin();

	return 0;
}
