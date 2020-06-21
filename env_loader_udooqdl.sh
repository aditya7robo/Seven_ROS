#!/bin/bash
export ROS_MASTER_URI=http://sevenRobot1:11311
export ROS_HOSTNAME=192.168.0.23
export ROS_IP=192.168.0.23

exec "$@"
