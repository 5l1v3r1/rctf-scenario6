#!/bin/bash

source /opt/ros/kinetic/setup.bash

roscore > /dev/null &
sleep 4
rosrun scenario6 asker &
bash
