// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_msgs:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_MSGS__MSG__MOTOR_DATA__FUNCTIONS_H_
#define MOTOR_MSGS__MSG__MOTOR_DATA__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_generator_c/visibility_control.h"
#include "motor_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "motor_msgs/msg/motor_data__struct.h"

/// Initialize msg/MotorData message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * motor_msgs__msg__MotorData
 * )) before or use
 * motor_msgs__msg__MotorData__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
bool
motor_msgs__msg__MotorData__init(motor_msgs__msg__MotorData * msg);

/// Finalize msg/MotorData message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
void
motor_msgs__msg__MotorData__fini(motor_msgs__msg__MotorData * msg);

/// Create msg/MotorData message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * motor_msgs__msg__MotorData__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
motor_msgs__msg__MotorData *
motor_msgs__msg__MotorData__create();

/// Destroy msg/MotorData message.
/**
 * It calls
 * motor_msgs__msg__MotorData__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
void
motor_msgs__msg__MotorData__destroy(motor_msgs__msg__MotorData * msg);


/// Initialize array of msg/MotorData messages.
/**
 * It allocates the memory for the number of elements and calls
 * motor_msgs__msg__MotorData__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
bool
motor_msgs__msg__MotorData__Sequence__init(motor_msgs__msg__MotorData__Sequence * array, size_t size);

/// Finalize array of msg/MotorData messages.
/**
 * It calls
 * motor_msgs__msg__MotorData__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
void
motor_msgs__msg__MotorData__Sequence__fini(motor_msgs__msg__MotorData__Sequence * array);

/// Create array of msg/MotorData messages.
/**
 * It allocates the memory for the array and calls
 * motor_msgs__msg__MotorData__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
motor_msgs__msg__MotorData__Sequence *
motor_msgs__msg__MotorData__Sequence__create(size_t size);

/// Destroy array of msg/MotorData messages.
/**
 * It calls
 * motor_msgs__msg__MotorData__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_msgs
void
motor_msgs__msg__MotorData__Sequence__destroy(motor_msgs__msg__MotorData__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_MSGS__MSG__MOTOR_DATA__FUNCTIONS_H_
