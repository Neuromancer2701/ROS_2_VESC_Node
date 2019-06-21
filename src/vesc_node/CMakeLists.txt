cmake_minimum_required(VERSION 3.5)
project(vesc_node)

set(CMAKE_CXX_STANDARD 14)

include_directories(.
                    /opt/ros/dashing/include/)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)


add_executable(vesc_node
        vescnode.cpp
        vescnode.h
        publisher_node.cpp
        publisher_node.hpp
        subscriber_node.cpp
        subscriber_node.hpp
        visibility.h)
