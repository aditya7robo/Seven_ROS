cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(seven_msgs)

find_package(catkin REQUIRED COMPONENTS
				genmsg
				roscpp
				rospy
				std_msgs
				message_generation
			)

add_message_files(
				FILES
				AdisImu.msg
				)

generate_messages(
				DEPENDENCIES
				std_msgs)

catkin_package(CATKIN_DEPENDS message_runtime)
