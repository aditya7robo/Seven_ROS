/****************************************************************************
 * *	Copyright (C) 2019-20122 Seven Robotics. All rights reserved.
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

#include <ros/ros.h>
#include <urdf/model.h>

bool isOnRight(urdf::Pose& p)
{
 //Following REP-103 default co-ordinate system.North,West,Up
 if(p.position.y < 0)
  return true;

 return false;
}

template<class Type,class Element>
struct hasType
{
};

template<class Type>
struct hasType<Type,urdf::CollisionSharedPtr>
{
  hasType(Type t)
  {
   if(t->collision==nullptr)
    value=false;
   else
    value=true;
  }
 
 bool value=false;
};

template<class Type>
struct hasType<Type,urdf::VisualSharedPtr>
{
 hasType(Type t)
 {
   if(t->visual==nullptr)
    value=false;
   else
    value=true;
 }
 bool value=false;
};

int main(int argc,char** argv) 
{
 ros::init(argc,argv,"urdfParser");
 ros::NodeHandle nh;

 urdf::Model robot_model;
 std::string robot_name;
 std::vector<std::string> rightLinks,leftLinks;
 std::string rightLink,leftLink;
 std::vector<urdf::LinkSharedPtr> links;
 
 nh.getParam("robot_description",robot_name);
 robot_model.initString(robot_name);
 
 robot_model.getLinks(links);
 std::cout << "read urdf. Found "<<links.size()<<" links\n";
 

/* if(rightLinks.size()>1)
 {
  ROS_DEBUG_NAMED("robotParser","More than one right drive links found, %ld. Using the first for joint state publishing",
						rightLinks.size());
 }

 if(leftLinks.size()>1)
 {
  ROS_DEBUG_NAMED("robotParser","More than one left drive links found, %ld. Using the first for joint state publishing",
						leftLinks.size());
 }

 nh.param<std::string>("/rightLink",rightLinks.front(),"Right");
 nh.param<std::string>("/leftLink",leftLinks.front(),"Left");
 ros::spin();*/
}
