#!/bin/bash
export ROS_ROOT=/opt/ros
export ROS_DISTRO=kinetic
export ROS_PACKAGE_PATH=/opt/ros/kinetic/share
export PATH=$PATH:/opt/ros/kinetic/bin
export LD_LIBRARY_PATH=/opt/ros/kinetic/lib
export PYTHONPATH=/opt/ros/kinetic/lib/python2.7/site-packages
export ROS_MASTER_URI=http://sevenRobot1:11311
export ROS_HOSTNAME=192.168.1.23
export ROS_IP=192.168.1.23
export CMAKE_PREFIX_PATH=/opt/ros/kinetic
touch /opt/ros/kinetic/.catkinexport 

exec "$@"
