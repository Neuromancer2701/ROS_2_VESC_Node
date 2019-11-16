cmake_minimum_required(VERSION 3.11)
project(vesc_pub_sub)

# Default to C++17
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(.
        /opt/ros/dashing/include/
        inc/
        )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files 
   "msg/MotorData.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
   ${msg_files}
   DEPENDENCIES std_msgs
)

add_executable(vesc_node vesc_node.cpp)
ament_target_dependencies(vesc_node rclcpp std_msgs)
rosidl_target_interfaces(vesc_node ${PROJECT_NAME} "rosidl_typesupport_cpp")

ament_package()

install(TARGETS
        vesc_node
        DESTINATION lib/${PROJECT_NAME})


#colcon build --packages-select
