// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_msgs:msg/MotorData.idl
// generated code does not contain a copyright notice
#include "motor_msgs/msg/motor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
motor_msgs__msg__MotorData__init(motor_msgs__msg__MotorData * msg)
{
  if (!msg) {
    return false;
  }
  // current
  // voltage
  // speed
  return true;
}

void
motor_msgs__msg__MotorData__fini(motor_msgs__msg__MotorData * msg)
{
  if (!msg) {
    return;
  }
  // current
  // voltage
  // speed
}

motor_msgs__msg__MotorData *
motor_msgs__msg__MotorData__create()
{
  motor_msgs__msg__MotorData * msg = (motor_msgs__msg__MotorData *)malloc(sizeof(motor_msgs__msg__MotorData));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_msgs__msg__MotorData));
  bool success = motor_msgs__msg__MotorData__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
motor_msgs__msg__MotorData__destroy(motor_msgs__msg__MotorData * msg)
{
  if (msg) {
    motor_msgs__msg__MotorData__fini(msg);
  }
  free(msg);
}


bool
motor_msgs__msg__MotorData__Sequence__init(motor_msgs__msg__MotorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  motor_msgs__msg__MotorData * data = NULL;
  if (size) {
    data = (motor_msgs__msg__MotorData *)calloc(size, sizeof(motor_msgs__msg__MotorData));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_msgs__msg__MotorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_msgs__msg__MotorData__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
motor_msgs__msg__MotorData__Sequence__fini(motor_msgs__msg__MotorData__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      motor_msgs__msg__MotorData__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

motor_msgs__msg__MotorData__Sequence *
motor_msgs__msg__MotorData__Sequence__create(size_t size)
{
  motor_msgs__msg__MotorData__Sequence * array = (motor_msgs__msg__MotorData__Sequence *)malloc(sizeof(motor_msgs__msg__MotorData__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = motor_msgs__msg__MotorData__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
motor_msgs__msg__MotorData__Sequence__destroy(motor_msgs__msg__MotorData__Sequence * array)
{
  if (array) {
    motor_msgs__msg__MotorData__Sequence__fini(array);
  }
  free(array);
}
