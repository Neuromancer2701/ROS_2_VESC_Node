cmake_minimum_required(VERSION 3.10)
project(vesc_pub_sub)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()



find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(PkgConfig)
pkg_check_modules(SERIAL libserial)



include_directories(.
        lib/libVESC/inc
        lib/libVESC
        /usr/include/libserial)

set(msg_files
   "msg/MotorData.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
   ${msg_files}
   DEPENDENCIES std_msgs
)

link_directories(/usr/lib/x86_64-linux-gnu/
                 lib/libVESC)


if(NOT WIN32)
  ament_environment_hooks(
          "${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}"
  )
endif()

set(vesc_lib
        "libVESC.so"
        )

add_executable(vesc_node vesc_node.cpp)
target_link_libraries(vesc_node ${SERIAL_LIBRARIES} ${vesc_lib})
target_include_directories(vesc_node PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

ament_target_dependencies(vesc_node rclcpp std_msgs geometry_msgs)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(vesc_node "${cpp_typesupport_target}")


install(TARGETS
        vesc_node
        DESTINATION lib/${PROJECT_NAME})

ament_package()


#colcon build --packages-select vesc_pub_sub
