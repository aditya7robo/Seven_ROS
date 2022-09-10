#!/bin/bash
export ROS_ROOT=/opt/ros
export ROS_DISTRO=melodic
export ROS_PACKAGE_PATH=/opt/ros/melodic/share
export PATH=$PATH:/opt/ros/melodic/bin
export LD_LIBRARY_PATH=/opt/ros/melodic/lib
export PYTHONPATH=/opt/ros/melodic/lib/python2.7/site-packages
export ROS_MASTER_URI=http://sevenRobot1:11311
export ROS_HOSTNAME=udooqdl
export ROS_IP=192.168.1.23
export CMAKE_PREFIX_PATH=/opt/ros/melodic
touch /opt/ros/melodic/.catkinexport 

exec "$@"
