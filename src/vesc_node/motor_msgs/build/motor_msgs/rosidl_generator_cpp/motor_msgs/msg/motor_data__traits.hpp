// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_msgs:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_MSGS__MSG__MOTOR_DATA__TRAITS_HPP_
#define MOTOR_MSGS__MSG__MOTOR_DATA__TRAITS_HPP_

#include "motor_msgs/msg/motor_data__struct.hpp"
#include <rosidl_generator_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<motor_msgs::msg::MotorData>()
{
  return "motor_msgs::msg::MotorData";
}

template<>
struct has_fixed_size<motor_msgs::msg::MotorData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<motor_msgs::msg::MotorData>
  : std::integral_constant<bool, true> {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_MSGS__MSG__MOTOR_DATA__TRAITS_HPP_
