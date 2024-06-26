// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces_ros2_pkg:msg/CustomMsg.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES_ROS2_PKG__MSG__DETAIL__CUSTOM_MSG__STRUCT_H_
#define CUSTOM_INTERFACES_ROS2_PKG__MSG__DETAIL__CUSTOM_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'child_frame_id'
#include "rosidl_runtime_c/string.h"
// Member 'pose_modified'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.h"

/// Struct defined in msg/CustomMsg in the package custom_interfaces_ros2_pkg.
typedef struct custom_interfaces_ros2_pkg__msg__CustomMsg
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String child_frame_id;
  bool custom_bool;
  int8_t custom_int;
  double custom_double;
  geometry_msgs__msg__PoseWithCovarianceStamped pose_modified;
} custom_interfaces_ros2_pkg__msg__CustomMsg;

// Struct for a sequence of custom_interfaces_ros2_pkg__msg__CustomMsg.
typedef struct custom_interfaces_ros2_pkg__msg__CustomMsg__Sequence
{
  custom_interfaces_ros2_pkg__msg__CustomMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces_ros2_pkg__msg__CustomMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES_ROS2_PKG__MSG__DETAIL__CUSTOM_MSG__STRUCT_H_
