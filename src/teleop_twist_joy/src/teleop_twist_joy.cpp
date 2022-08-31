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
#include <cmath>
#include <numbers>
#include <chrono>

#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "teleop_twist_joy/teleop_twist_joy.h"


namespace teleop_twist_joy
{
    using namespace std::numbers;
    using namespace std::chrono_literals;
    using namespace std::chrono::steady_clock;
    using namespace std::chrono::time_point;

    constexpr double MILLISECOND_COUNT{1000.0};


/**
 * Internal members of class. This is the pimpl idiom, and allows more flexibility in adding
 * parameters later without breaking ABI compatibility, for robots which link TeleopTwistJoy
 * directly into base nodes.
 */
    struct TeleopTwistJoy::Impl
    {
        void joyCallback(const sensor_msgs::Joy::ConstPtr &joy);

        void sendCmdVelMsg(const sensor_msgs::Joy::ConstPtr &joy_msg, const std::string &which_map);

        ros::Subscriber joy_sub;
        ros::Publisher cmd_vel_pub;

        std::map<std::string, int> axis_linear_map;
        std::map< std::string, std::map<std::string, double> > scale_linear_map;

        std::map<std::string, int> axis_angular_map;
        std::map< std::string, std::map<std::string, double> > scale_angular_map;


        int64_t enable_button;
        bool sent_disable_msg;
        time_point previousTime_ms{0ms};
        time_point currentTime_ms{0ms};
        double previousTheta_angle;
        double currentTheta_angle;
    };

/**
 * Constructs TeleopTwistJoy.
 */
    TeleopTwistJoy::TeleopTwistJoy(ros::NodeHandle* nh, ros::NodeHandle* nh_param)
    {
        pimpl_ = new Impl;

        pimpl_->cmd_vel_pub = nh->advertise<geometry_msgs::Twist>("cmd_vel", 1, true);
        pimpl_->joy_sub = nh->subscribe<sensor_msgs::Joy>("joy", 1, &TeleopTwistJoy::Impl::joyCallback, pimpl_);

        nh_param->param<int>("enable_button", pimpl_->enable_button, 0);

        if (nh_param->getParam("axis_linear", pimpl_->axis_linear_map))
        {
            nh_param->getParam("scale_linear", pimpl_->scale_linear_map["normal"]);
        }
        else
        {
            nh_param->param<int>("axis_linear", pimpl_->axis_linear_map["x"], 1);
            nh_param->param<double>("scale_linear", pimpl_->scale_linear_map["normal"]["x"], 0.5);
        }

        if (nh_param->getParam("axis_angular", pimpl_->axis_angular_map))
        {
            nh_param->getParam("scale_angular", pimpl_->scale_angular_map["normal"]);
        }
        else
        {
            nh_param->param<int>("axis_angular", pimpl_->axis_angular_map["yaw"], 0);
            nh_param->param<double>("scale_angular", pimpl_->scale_angular_map["normal"]["yaw"], 0.5);
        }

        ROS_INFO_NAMED("TeleopTwistJoy", "Teleop enable button %i.", pimpl_->enable_button);

        for (std::map<std::string, int>::iterator it = pimpl_->axis_linear_map.begin();
             it != pimpl_->axis_linear_map.end(); ++it)
        {
            ROS_INFO_NAMED("TeleopTwistJoy", "Linear axis %s on %i at scale %f.",
                           it->first.c_str(), it->second, pimpl_->scale_linear_map["normal"][it->first]);
        }

        for (std::map<std::string, int>::iterator it = pimpl_->axis_angular_map.begin();
             it != pimpl_->axis_angular_map.end(); ++it)
        {
            ROS_INFO_NAMED("TeleopTwistJoy", "Angular axis %s on %i at scale %f.",
                           it->first.c_str(), it->second, pimpl_->scale_angular_map["normal"][it->first]);
        }

        pimpl_->sent_disable_msg = false;

        RCUTILS_LOG_INFO("%s ", __PRETTY_FUNCTION__);
    }

    TeleopTwistJoy::~TeleopTwistJoy() {
        delete pimpl_;
    }


    void TeleopTwistJoy::Impl::sendCmdVelMsg(const sensor_msgs::Joy::ConstPtr& joy_msg)
    {

#if 0
        // Initializes with zeros by default.
        cmd_vel_msg.linear.x = getVal(joy_msg, axis_linear_map, scale_linear_map[which_map], "x");
        cmd_vel_msg.linear.y = getVal(joy_msg, axis_linear_map, scale_linear_map[which_map], "y");
        cmd_vel_msg.linear.z = getVal(joy_msg, axis_linear_map, scale_linear_map[which_map], "z");
        cmd_vel_msg.angular.z = getVal(joy_msg, axis_angular_map, scale_angular_map[which_map], "yaw");
        cmd_vel_msg.angular.y = getVal(joy_msg, axis_angular_map, scale_angular_map[which_map], "pitch");
        cmd_vel_msg.angular.x = getVal(joy_msg, axis_angular_map, scale_angular_map[which_map], "roll");
#endif

        auto x{joy_msg->axes[0]};
        auto y{joy_msg->axes[1]};

        auto magnitude{hypot(x,y)};
        previousTheta_angle = currentTheta_angle;
        currentTheta_angle = atan2(y, x) * 180 / pi;

        previousTime_ms = currentTime_ms;
        currentTime_ms = steady_clock.now();
        auto delta{(currentTime_ms.count() - previousTime_ms.count()) / MILLISECOND_COUNT};

        geometry_msgs::Twist cmd_vel_msg;
        cmd_vel_msg->linear.x = magnitude;
        cmd_vel_msg->angular.z = ((currentTheta_angle - previousTheta_angle) / delta);

        cmd_vel_pub->publish(std::move(cmd_vel_msg));
        sent_disable_msg = false;
    }

    void TeleopTwistJoy::Impl::joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg) {
        if (static_cast<int>(joy_msg->buttons.size()) > enable_button &&
            joy_msg->buttons[enable_button]) {
            sendCmdVelMsg(joy_msg);
        } else {
            // When enable button is released, immediately send a single no-motion command
            // in order to stop the robot.
            if (!sent_disable_msg) {
                // Initializes with zeros by default.
                auto cmd_vel_msg = std::make_unique<geometry_msgs::msg::Twist>();
                cmd_vel_pub->publish(std::move(cmd_vel_msg));
                sent_disable_msg = true;
            }
        }
    }

}  // namespace teleop_twist_joy

