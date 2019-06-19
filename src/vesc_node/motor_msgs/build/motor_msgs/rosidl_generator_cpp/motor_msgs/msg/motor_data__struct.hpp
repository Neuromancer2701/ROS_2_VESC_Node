// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_msgs:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_MSGS__MSG__MOTOR_DATA__STRUCT_HPP_
#define MOTOR_MSGS__MSG__MOTOR_DATA__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

// Protect against ERROR being predefined on Windows, in case somebody defines a
// constant by that name.
#if defined(_WIN32)
  #if defined(ERROR)
    #undef ERROR
  #endif
  #if defined(NO_ERROR)
    #undef NO_ERROR
  #endif
#endif

#ifndef _WIN32
# define DEPRECATED__motor_msgs__msg__MotorData __attribute__((deprecated))
#else
# define DEPRECATED__motor_msgs__msg__MotorData __declspec(deprecated)
#endif

namespace motor_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorData_
{
  using Type = MotorData_<ContainerAllocator>;

  explicit MotorData_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->current = 0.0;
      this->voltage = 0.0;
      this->speed = 0.0;
    }
  }

  explicit MotorData_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->current = 0.0;
      this->voltage = 0.0;
      this->speed = 0.0;
    }
  }

  // field types and members
  using _current_type =
    double;
  _current_type current;
  using _voltage_type =
    double;
  _voltage_type voltage;
  using _speed_type =
    double;
  _speed_type speed;

  // setters for named parameter idiom
  Type & set__current(
    const double & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__voltage(
    const double & _arg)
  {
    this->voltage = _arg;
    return *this;
  }
  Type & set__speed(
    const double & _arg)
  {
    this->speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_msgs::msg::MotorData_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_msgs::msg::MotorData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_msgs::msg::MotorData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_msgs::msg::MotorData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_msgs::msg::MotorData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_msgs::msg::MotorData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_msgs::msg::MotorData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_msgs::msg::MotorData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_msgs::msg::MotorData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_msgs::msg::MotorData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_msgs__msg__MotorData
    std::shared_ptr<motor_msgs::msg::MotorData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_msgs__msg__MotorData
    std::shared_ptr<motor_msgs::msg::MotorData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorData_ & other) const
  {
    if (this->current != other.current) {
      return false;
    }
    if (this->voltage != other.voltage) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorData_

// alias to use template instance with default allocator
using MotorData =
  motor_msgs::msg::MotorData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_msgs

#endif  // MOTOR_MSGS__MSG__MOTOR_DATA__STRUCT_HPP_
