cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(imu_uavcanros)

find_library(UAVCAN_LIB uavcan required)

find_package(catkin REQUIRED COMPONENTS
				roscpp
				rospy
				seven_msgs
				std_msgs
				sensor_msgs
				message_generation
			)

generate_message(DEPENDENCIES std_msgs)

catkin_package(DEPENDS roscpp)

FILE(GLOB SRCS *.cpp)
add_executable(ros_uavcan ${SRCS})
target_link_libraries(ros_uavcan ${UAVCAN_LIB} rt ${catkin_LIBRARIES})
