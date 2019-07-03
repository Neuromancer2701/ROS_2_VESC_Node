//
// Created by root on 6/25/19.
//

#include "vesc_node.h"

using std::lock_guard;

VescNode::VescNode(rclcpp::Node::SharedPtr n):counter(0), node_(n)
{

}

void VescNode::onInit()
{
    vescApi.FindandMapMotorControllers();

    if(vescApi.isTwoWheelDrive())
    {
        publisher_ = node_->create_publisher<MotorData>("topic", 10);
        pub_timer_ = node_->create_wall_timer( 50ms, std::bind(&VescNode::timer_callback, this));
        subscription_ = node_->create_subscription<Twist>("topic", 10, std::bind(&VescNode::twist_callback, this, _1));
    }
    else
    {
        RCLCPP_INFO(node_->get_logger(), "Found not find all required wheels");
    }

}

void VescNode::timer_callback()
{
    auto wheelRpms = getWheelRpms();
    vescApi.SetWheelsRPM(wheelRpms);

    if(counter++ > PUB_INTERVAL)
    {
        //vescApi.getMotorData;
        auto message = MotorData();
        message.current  = 1.235;
        message.speed    = 2.456;
        message.voltage  = 39.78;
        //RCLCPP_INFO(this->get_logger(), "Publisher: '%s'", message.data.c_str());
        publisher_->publish(message);
        counter = 0;
    }
}

void VescNode::twist_callback(Twist msg)
{
    int K = 32;
    map<int, int> wheelRpms;
    wheelRpms[Vesc::left_back]  = static_cast<int>(msg.linear.x - K * msg.angular.z);
    wheelRpms[Vesc::right_back] = static_cast<int>(msg.linear.x + K * msg.angular.z);

    setWheelRpms(wheelRpms);
}

map<int, int> &VescNode::getWheelRpms()
{
    lock_guard<std::mutex> lock(rpm_mutex);
    return wheel_rpms;
}

void VescNode::setWheelRpms(const map<int, int> &wheelRpms)
{
    lock_guard<std::mutex> lock(rpm_mutex);
    wheel_rpms = wheelRpms;
}
