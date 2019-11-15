cmake_minimum_required(VERSION 3.5)
project(minimal_chatter)

if(NOT CMAKE_CXX_STANDARD)
   set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files 
   "msg/LNumM.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
   ${msg_files}
   DEPENDENCIES std_msgs
)

add_executable(subscriber_lambda lambda_sub.cpp)
ament_target_dependencies(subscriber_lambda rclcpp std_msgs)
rosidl_target_interfaces(subscriber_lambda ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(publisher_lambda lambda_pub.cpp)
ament_target_dependencies(publisher_lambda rclcpp std_msgs)
rosidl_target_interfaces(publisher_lambda ${PROJECT_NAME} "rosidl_typesupport_cpp")

ament_package()

install(TARGETS 
   subscriber_lambda
   publisher_lambda
   DESTINATION lib/${PROJECT_NAME}
)
