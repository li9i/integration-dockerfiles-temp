cmake_minimum_required(VERSION 3.8)
project(custom_interfaces_ros2_pkg)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/CustomMsg.msg"
  DEPENDENCIES std_msgs geometry_msgs
 )
ament_export_dependencies(rosidl_default_runtime)

install(
  FILES msg/my_mapping_rules.yaml
  DESTINATION share/${PROJECT_NAME}/msg)


ament_package()
