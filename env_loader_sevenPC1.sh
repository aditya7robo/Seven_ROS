#!/bin/bash
export ROS_WS=/home/talha/Seven_ROS
source $ROS_WS/devel/setup.bash
export PATH=$ROS_ROOT/bin:$PATH
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$ROS_WS
export ROS_MASTER_URI=http://sevenrobot2:11311
export ROS_HOSTNAME=sevenPC1

export DISPLAY=:0
exec "$@"
