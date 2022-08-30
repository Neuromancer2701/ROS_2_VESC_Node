cmake_minimum_required(VERSION 3.10)
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

add_library(serial_library SHARED
        lib/libVESC/inc/libserial/SerialPort.)
target_compile_definitions(serial_library PRIVATE "VESC_NODE_DLL")

add_library(vesc_library SHARED
        lib/libVESC/commands.cpp
        lib/libVESC/packet.cpp
        lib/libVESC/Vesc.cpp)
target_compile_definitions(vesc_library PRIVATE "VESC_NODE_DLL")

if(NOT WIN32)
  ament_environment_hooks(
          "${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}"
  )
endif()


add_executable(vesc_node vesc_node.cpp)
target_link_libraries(vesc_node vesc_library serial_library )
ament_target_dependencies(vesc_node rclcpp std_msgs geometry_msgs)
rosidl_target_interfaces(vesc_node ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
        serial_library
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(TARGETS
        vesc_library
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(TARGETS
        vesc_node
        DESTINATION lib/${PROJECT_NAME})

ament_package()


#colcon build --packages-select
