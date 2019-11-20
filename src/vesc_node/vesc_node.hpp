//
// Created by Seth M King on 6/25/19.
//

#ifndef VESC_NODE_H
#define VESC_NODE_H

#include <chrono>
#include <memory>
#include <map>
#include <mutex>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "vesc_pub_sub/msg/motor_data.hpp"
#include "geometry_msgs/msg/twist.hpp"



#include "inc/Vesc.h"

using std::mutex;
using std::map;
using vesc_pub_sub::msg::MotorData;
using geometry_msgs::msg::Twist;

class VescNode: public rclcpp::Node
{
public:
    VescNode();
    void onInit();

private:
    unsigned long long counter;
    rclcpp::TimerBase::SharedPtr pub_timer_;
    rclcpp::Publisher<MotorData>::SharedPtr publisher_;

    rclcpp::Subscription<Twist>::SharedPtr subscription_;
    void twist_callback(const Twist::SharedPtr msg);
    void timer_callback();

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
