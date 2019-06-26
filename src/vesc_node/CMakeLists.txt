cmake_minimum_required(VERSION 3.5)
project(vesc_node)

set(CMAKE_CXX_STANDARD 14)

include_directories(.
                    /opt/ros/dashing/include/
                    motor_msgs/install/motor_msgs/include/)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
#find_package(motor_msgs REQUIRED)


add_executable(vesc_node
        publisher_node.cpp
        publisher_node.hpp
        subscriber_node.cpp
        subscriber_node.hpp
        visibility.h vesc_node.cpp vesc_node.h)
