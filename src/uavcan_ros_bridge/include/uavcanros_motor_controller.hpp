/****************************************************************************
 * *	Copyright (C) 2016-2019 Seven Robotics. All rights reserved.
 * *	Author: Mohammed Talha Arif  <mtalha@sevenrobotics.in>
 * *
 * *  Redistribution and use in source and binary forms, with or without
 * *  modification, are permitted provided that the following conditions
 * *  are met:
 * *
 * *  1. Redistributions of source code must retain the above copyright
 * *     notice, this list of conditions and the following disclaimer.
 * *  2. Redistributions in binary form must reproduce the above copyright
 * *     notice, this list of conditions and the following disclaimer in
 * *     the documentation and/or other materials provided with the
 * *     distribution.
 * * 	3. Neither the name Seven Robotics nor the names of its contributors
 * * 		 may be used to endorse or promote products derived from this
 * * 		 software without specific prior written permission.
 * *
 * *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * *  POSSIBILITY OF SUCH DAMAGE.
 * *
 * ****************************************************************************/

#pragma once

#include <iostream>
#include <functional>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <geometry_msgs/Twist.h>
#include <uavcan/uavcan.hpp>
#include <uavcan_ros_bridge/robotParamsConfig.h>
#include <uavcan/equipment/actuator/CmdRpm.hpp>
#include <uavcan/equipment/encoder/Encoder.hpp>
#include <seven_robotics_msgs/MotorEncoder.h>


namespace uavcanMotor {

enum rosEncoderID: uint8_t {
	left = 0x001,
	right= 0x010 
};

class motorController {
private:

static const int MemoryBlockPoolSize=16384;
using Node = uavcan::Node<MemoryBlockPoolSize>;
std::string topicName;
ros::NodeHandle& _nh;
Node& node;
uavcan::Publisher<uavcan::equipment::actuator::CmdRpm> velPub;
uavcan::Subscriber<uavcan::equipment::encoder::Encoder> encSub;
seven_robotics_msgs::MotorEncoder rosEncoderMsg[2];

//robot parameters
struct robotDynamicParams {
double wheelRadius=0;
double wheelBase=0;

double maxLinearVel=0;
double maxAngularVel=0;
int odomPublishHz = 100;
//is feedBack available?
bool feedBack=false;
};

robotDynamicParams params;
//node parameters
ros::Time _startTime;
ros::Time _stopTime;
ros::Time _lastPublishTime;

using reconfigureServer = typename dynamic_reconfigure::Server<uavcan_ros_bridge::robotParamsConfig>;
reconfigureServer server;



public:
	ros::Subscriber sub;
	ros::Publisher pubLeftEncoder;
	ros::Publisher pubRightEncoder;
	void encoder_cb(const uavcan::equipment::encoder::Encoder&);
	void cmdCallback(const geometry_msgs::Twist& cmd);
	void brake();

	motorController(Node& n,ros::NodeHandle& nh,const std::string topic="cmd_vel"):topicName{topic},
																																						_nh{nh},node{n},velPub{n},encSub{n} 
																																					
	{
		sub = _nh.subscribe(topic,10,&motorController::cmdCallback,this);
		pubLeftEncoder = _nh.advertise<seven_robotics_msgs::MotorEncoder>("leftEncoder",50);
		pubRightEncoder = _nh.advertise<seven_robotics_msgs::MotorEncoder>("rightEncoder",50);
		
		_nh.getParam("wheelRadius",params.wheelRadius);
		_nh.getParam("wheelBase",params.wheelBase);
		_nh.getParam("maxLinearVel",params.maxLinearVel);
		_nh.getParam("maxAngularVel",params.maxAngularVel);

		/*only used during testing*/
		_nh.setParam("motorfeedBack",false);
		_nh.getParam("motorfeedBack",params.feedBack);
		const int sub_res = encSub.start([&](const uavcan::ReceivedDataStructure<uavcan::equipment::encoder::Encoder>& msg){
														this->encoder_cb(msg);});		
		if(sub_res < 0)
		{
			std::cout << "Failed to start uavcan encoder Subscriber\n";
		}
		const int pub_res = velPub.init();
		if(pub_res < 0)
		{
			std::cout << "Failed to start uavcan velocity Publisher\n";
		}
	}
	
};

}
