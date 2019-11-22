/**
Software License Agreement (BSD)

\authors   Mike Purvis <mpurvis@clearpathrobotics.com>
\copyright Copyright (c) 2014, Clearpath Robotics, Inc., All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that
the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the
   following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
   following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Clearpath Robotics nor the names of its contributors may be used to endorse or promote
   products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WAR-
RANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, IN-
DIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cinttypes>
#include <functional>
#include <map>
#include <memory>
#include <string>

#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <rcutils/logging_macros.h>
#include <sensor_msgs/msg/wiimote.hpp>

#include "teleop_twist_wiimote/teleop_twist_wiimote.hpp"

#define ROS_INFO_NAMED RCUTILS_LOG_INFO_NAMED
#define ROS_INFO_COND_NAMED RCUTILS_LOG_INFO_EXPRESSION_NAMED

namespace teleop_twist_wiimote
{

/**
 * Internal members of class. This is the pimpl idiom, and allows more flexibility in adding
 * parameters later without breaking ABI compatibility, for robots which link TeleopTwistWiimote
 * directly into base nodes.
 */
struct TeleopTwistWiimote::Impl
{
  void wiimoteCallback(const sensor_msgs::msg::Wiimote::SharedPtr wiimote);
  void sendCmdVelMsg(const sensor_msgs::msg::Wiimote::SharedPtr, const std::string& which_map);

  rclcpp::Subscription<sensor_msgs::msg::Wiimote>::SharedPtr wiimote_sub;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub;

  int64_t enable_button;

  bool sent_disable_msg;
};

/**
 * Constructs TeleopTwistWiimote.
 */
TeleopTwistWiimote::TeleopTwistWiimote(const rclcpp::NodeOptions& options) : Node("teleop_twist_wiimote_node", options)
{
  pimpl_ = new Impl;

  pimpl_->cmd_vel_pub = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  pimpl_->wiimote_sub = this->create_subscription<sensor_msgs::msg::Wiimote>("wiimote", rclcpp::QoS(10),
    std::bind(&TeleopTwistWiimote::Impl::wiimoteCallback, this->pimpl_, std::placeholders::_1));

  pimpl_->enable_button = this->declare_parameter("enable_button", 5);

  pimpl_->sent_disable_msg = false;
}

TeleopTwistWiimote::~TeleopTwistWiimote()
{
  delete pimpl_;
}

void TeleopTwistWiimote::Impl::sendCmdVelMsg(const sensor_msgs::msg::Wiimote::SharedPtr wiimote_msg,
                                         const std::string& which_map)
{
  // Initializes with zeros by default.
  auto cmd_vel_msg = std::make_unique<geometry_msgs::msg::Twist>();

  cmd_vel_msg->linear.x = getVal(wiimote_msg, axis_linear_map, scale_linear_map[which_map], "x");
  cmd_vel_msg->linear.y = getVal(wiimote_msg, axis_linear_map, scale_linear_map[which_map], "y");
  cmd_vel_msg->linear.z = getVal(wiimote_msg, axis_linear_map, scale_linear_map[which_map], "z");

  cmd_vel_pub->publish(std::move(cmd_vel_msg));
  sent_disable_msg = false;
}

void TeleopTwistWiimote::Impl::wiimoteCallback(const sensor_msgs::msg::Wiimote::SharedPtr wiimote_msg)
{
  if (enable_turbo_button >= 0 &&
      static_cast<int>(wiimote_msg->buttons.size()) > enable_turbo_button &&
      wiimote_msg->buttons[enable_turbo_button])
  {
    sendCmdVelMsg(wiimote_msg, "turbo");
  }
  else if (static_cast<int>(wiimote_msg->buttons.size()) > enable_button &&
           wiimote_msg->buttons[enable_button])
  {
    sendCmdVelMsg(wiimote_msg, "normal");
  }
  else
  {
    // When enable button is released, immediately send a single no-motion command
    // in order to stop the robot.
    if (!sent_disable_msg)
    {
      // Initializes with zeros by default.
      auto cmd_vel_msg = std::make_unique<geometry_msgs::msg::Twist>();
      cmd_vel_pub->publish(std::move(cmd_vel_msg));
      sent_disable_msg = true;
    }
  }
}

}  // namespace teleop_twist_wiimote

RCLCPP_COMPONENTS_REGISTER_NODE(teleop_twist_wiimote::TeleopTwistWiimote)
