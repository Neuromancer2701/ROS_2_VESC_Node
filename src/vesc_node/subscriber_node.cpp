// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <memory>

#include "subscriber_node.hpp"
#include "rclcpp/rclcpp.hpp"

using ::std::placeholders::_1;

SubscriberNode::SubscriberNode(rclcpp::NodeOptions options)
: Node("twist_subscriber_node", options)
{
  subscription_ = create_subscription<Twist>("topic", 10, std::bind(&SubscriberNode::twist_callback, this, _1));
}

void SubscriberNode::twist_callback(Twist msg)
{



}


#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(SubscriberNode)
