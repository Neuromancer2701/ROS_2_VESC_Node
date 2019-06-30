cmake_minimum_required(VERSION 3.5)
project(vesc_node)

set(CMAKE_CXX_STANDARD 14)

include_directories(.
                    /opt/ros/dashing/include/
                    motor_msgs/install/motor_msgs/include/
                    inc/
                    )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
#find_package(motor_msgs REQUIRED)


add_executable(vesc_node
        vesc_node.cpp
        vesc_node.h
        visibility.h
        inc/Vesc.h
        inc/packet.h
        inc/datatypes.h
        )
