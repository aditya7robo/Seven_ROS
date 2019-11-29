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

#include <uavcanros_motor_controller.hpp>

namespace uavcanMotor {

void motorController::encoder_cb(const uavcan::equipment::encoder::encoder& msg) {
			rosEncodermsg[0].timestamp = rosEncodermsg[1].timestamp = ros::Time::now();
			rosEncodermsg[0].encoderID = rosEncoderID::left //left
			rosEncodermsg[0].ticks = msg.ticks[0];
			rosEncodermsg[0].totalCount = msg.totalCount[0];
			rosEncodermsg[1].encoderID = rosEncoderID::right //left
			rosEncodermsg[1].ticks = msg.ticks[1];
			rosEncodermsg[1].totalCount = msg.totalCount[1];

			if(pubLeftEncoder.isLatched())
			{
				pubLeftEncoder.publish(&rosEncodermsg[0]);
			}
			if(pubRightEncoder.isLatched())
			{
				pubRightEncoder.publish(&rosEncodermsg[1]);
			}
}

void motorController::cmdCallback(const geometry_msgs::Twist& cmd) {
	
}

void motorController::brake();
}
