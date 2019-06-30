//
// Created by Seth M King on 6/25/19.
//

#ifndef VESC_NODE_H
#define VESC_NODE_H

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "motor_msgs/msg/motor_data.hpp"
#include "inc/Vesc.h"

using geometry_msgs::msg::Twist;
using motor_msgs::msg::MotorData;
using std::placeholders::_1;
using namespace std::chrono_literals;
using std::mutex;

class vesc_node :public rclcpp::Node
{
public:
    vesc_node();

private:
    void timer_callback();
    rclcpp::TimerBase::SharedPtr pub_timer_;
    rclcpp::Publisher<MotorData>::SharedPtr publisher_;

    rclcpp::Subscription<Twist>::SharedPtr subscription_;
    void twist_callback(Twist msg);


    unsigned long long counter;

    enum constants
    {
        PUB_INTERVAL = 10
    };

    Vesc vescApi;
    mutex  rpm_mutex;
    map<int, int> wheel_rpms;

    map<int, int> &getWheelRpms();
    void setWheelRpms(const map<int, int> &wheelRpms);

};


#endif //VESC_NODE_H
