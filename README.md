# ROS_2_VESC_Node
standalone ROS 2 Node that will communicate will VESC controllers via libVESC

Module that points to libVesc repo that will need libSerial installed.

docker build -t ros-dev .

docker run -v /home/countzero/repos/ROS_2_VESC_Node:/ros_ws -td --cap-add sys_ptrace -p127.0.0.1:2222:22 --name clion_remote_env ros-dev


ssh user@localhost -p2222

bash
Build libVesc
cd src/vesc_node/lib/libVESC/
cmake .
make

Build ros2 nodes
 . /opt/ros/rolling/setup.sh

