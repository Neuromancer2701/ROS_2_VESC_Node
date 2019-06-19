// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_msgs:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_MSGS__MSG__MOTOR_DATA__STRUCT_H_
#define MOTOR_MSGS__MSG__MOTOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/MotorData in the package motor_msgs.
typedef struct motor_msgs__msg__MotorData
{
  double current;
  double voltage;
  double speed;
} motor_msgs__msg__MotorData;

// Struct for a sequence of motor_msgs__msg__MotorData.
typedef struct motor_msgs__msg__MotorData__Sequence
{
  motor_msgs__msg__MotorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_msgs__msg__MotorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_MSGS__MSG__MOTOR_DATA__STRUCT_H_
