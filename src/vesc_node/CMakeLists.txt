cmake_minimum_required(VERSION 3.14)
project(vesc_node)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)


add_executable(vesc_node
        vescnode.cpp
        vescnode.h)
