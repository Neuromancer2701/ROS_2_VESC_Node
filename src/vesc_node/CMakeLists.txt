cmake_minimum_required(VERSION 3.11)
project(vesc_node)

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
find_package(rosidl_default_generators REQUIRED)


add_library(vesc_node SHARED
            vesc_node.cpp)

target_compile_definitions(vesc_node PRIVATE "VESC_NODE_DLL")
ament_target_dependencies(vesc_node rclcpp rclcpp_components )

# This package installs libraries without exporting them.
# Export the library path to ensure that the installed libraries are available.
if(NOT WIN32)
  ament_environment_hooks(
    "${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}"
    )
endif()

add_executable(v_node main.cpp)
target_link_libraries(v_node vesc_node)
ament_target_dependencies(v_node rclcpp class_loader)
rosidl_target_interfaces(v_node ${PROJECT_NAME} "rosidl_typesupport_cpp")

ament_package()

install(TARGETS
        vesc_node
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(TARGETS
        v_node
        DESTINATION lib/${PROJECT_NAME})


#colcon build --packages-select
