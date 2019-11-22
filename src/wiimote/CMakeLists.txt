cmake_minimum_required(VERSION 3.5)

project(wiimote)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)


set(msg_files
        "msg/IrSourceInfo.msg"
        "msg/State.msg"
        "msg/TimedSwitch.msg"
        )

rosidl_generate_interfaces(${PROJECT_NAME}
        ${msg_files}
        DEPENDENCIES geometry_msgs std_msgs sensor_msgs
        )

## Specify additional locations of header files
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


## C++ Wiimote Node: Declare cpp executables
add_executable(wiimote_node src/wiimote_controller.cpp src/stat_vector_3d.cpp)
target_link_libraries(wiimote_node ${catkin_LIBRARIES} bluetooth cwiid)
ament_target_dependencies(wiimote_node rclcpp std_msgs geometry_msgs class_loader)
rosidl_target_interfaces(wiimote_node ${PROJECT_NAME} "rosidl_typesupport_cpp")
## End of C++ Wiimote Node

## C++ Teleop for Wiimote Node: Declare cpp executables
add_executable(teleop_wiimote src/teleop_wiimote.cpp)
target_link_libraries(teleop_wiimote ${catkin_LIBRARIES})
ament_target_dependencies(teleop_wiimote rclcpp std_msgs geometry_msgs class_loader)
rosidl_target_interfaces(teleop_wiimote ${PROJECT_NAME} "rosidl_typesupport_cpp")
## End C++ Teleop for Wiimote Node

ament_package()


#install(TARGETS
#        composition_nodes
#        ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#        RUNTIME DESTINATION bin)

install(TARGETS
        wiimote_node
        teleop_wiimote
        DESTINATION lib/${PROJECT_NAME})


