// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces_ros2_pkg:msg/CustomMsg.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES_ROS2_PKG__MSG__DETAIL__CUSTOM_MSG__BUILDER_HPP_
#define CUSTOM_INTERFACES_ROS2_PKG__MSG__DETAIL__CUSTOM_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interfaces_ros2_pkg/msg/detail/custom_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interfaces_ros2_pkg
{

namespace msg
{

namespace builder
{

class Init_CustomMsg_pose_modified
{
public:
  explicit Init_CustomMsg_pose_modified(::custom_interfaces_ros2_pkg::msg::CustomMsg & msg)
  : msg_(msg)
  {}
  ::custom_interfaces_ros2_pkg::msg::CustomMsg pose_modified(::custom_interfaces_ros2_pkg::msg::CustomMsg::_pose_modified_type arg)
  {
    msg_.pose_modified = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces_ros2_pkg::msg::CustomMsg msg_;
};

class Init_CustomMsg_custom_double
{
public:
  explicit Init_CustomMsg_custom_double(::custom_interfaces_ros2_pkg::msg::CustomMsg & msg)
  : msg_(msg)
  {}
  Init_CustomMsg_pose_modified custom_double(::custom_interfaces_ros2_pkg::msg::CustomMsg::_custom_double_type arg)
  {
    msg_.custom_double = std::move(arg);
    return Init_CustomMsg_pose_modified(msg_);
  }

private:
  ::custom_interfaces_ros2_pkg::msg::CustomMsg msg_;
};

class Init_CustomMsg_custom_int
{
public:
  explicit Init_CustomMsg_custom_int(::custom_interfaces_ros2_pkg::msg::CustomMsg & msg)
  : msg_(msg)
  {}
  Init_CustomMsg_custom_double custom_int(::custom_interfaces_ros2_pkg::msg::CustomMsg::_custom_int_type arg)
  {
    msg_.custom_int = std::move(arg);
    return Init_CustomMsg_custom_double(msg_);
  }

private:
  ::custom_interfaces_ros2_pkg::msg::CustomMsg msg_;
};

class Init_CustomMsg_custom_bool
{
public:
  explicit Init_CustomMsg_custom_bool(::custom_interfaces_ros2_pkg::msg::CustomMsg & msg)
  : msg_(msg)
  {}
  Init_CustomMsg_custom_int custom_bool(::custom_interfaces_ros2_pkg::msg::CustomMsg::_custom_bool_type arg)
  {
    msg_.custom_bool = std::move(arg);
    return Init_CustomMsg_custom_int(msg_);
  }

private:
  ::custom_interfaces_ros2_pkg::msg::CustomMsg msg_;
};

class Init_CustomMsg_child_frame_id
{
public:
  explicit Init_CustomMsg_child_frame_id(::custom_interfaces_ros2_pkg::msg::CustomMsg & msg)
  : msg_(msg)
  {}
  Init_CustomMsg_custom_bool child_frame_id(::custom_interfaces_ros2_pkg::msg::CustomMsg::_child_frame_id_type arg)
  {
    msg_.child_frame_id = std::move(arg);
    return Init_CustomMsg_custom_bool(msg_);
  }

private:
  ::custom_interfaces_ros2_pkg::msg::CustomMsg msg_;
};

class Init_CustomMsg_header
{
public:
  Init_CustomMsg_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CustomMsg_child_frame_id header(::custom_interfaces_ros2_pkg::msg::CustomMsg::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CustomMsg_child_frame_id(msg_);
  }

private:
  ::custom_interfaces_ros2_pkg::msg::CustomMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces_ros2_pkg::msg::CustomMsg>()
{
  return custom_interfaces_ros2_pkg::msg::builder::Init_CustomMsg_header();
}

}  // namespace custom_interfaces_ros2_pkg

#endif  // CUSTOM_INTERFACES_ROS2_PKG__MSG__DETAIL__CUSTOM_MSG__BUILDER_HPP_
