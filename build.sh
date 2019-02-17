#!/usr/bin/env bash

source devel/setup.bash
export UAVCAN_LIB=$(pwd)/src/libuavcan/build/libuavcan/libuavcan.a
catkin_make 
