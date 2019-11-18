//
// Created by Seth King on 6/25/19.
//

#include "vesc_node.hpp"


using std::placeholders::_1;
using namespace std::chrono_literals;
using std::mutex;
using std::map;
using std::lock_guard;


VescNode::VescNode():Node("vesc_pub_sub"), counter(0)
{
    onInit();
}

void VescNode::onInit()
{
    //vescApi.FindandMapMotorControllers();

    //if(vescApi.isTwoWheelDrive())
    {

        publisher_ =    this->create_publisher<MotorData>("motor_data", 10);
        pub_timer_ =    this->create_wall_timer( 50ms, std::bind(&VescNode::timer_callback, this));
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", rclcpp::QoS(10), std::bind(&VescNode::twist_callback, this, _1));
    }
    //else
    {
        //    RCLCPP_INFO(node_->get_logger(), "Found not find all required wheels");
    }

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

void VescNode::timer_callback()
{
#if disabled
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
#endif
}

void VescNode::twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
{
    int K = 32;
    map<int, int> wheelRpms;
    wheelRpms[2/*Vesc::left_back*/]  = static_cast<int>(msg->linear.x - K * msg->angular.z);
    wheelRpms[3/*Vesc::right_back*/] = static_cast<int>(msg->linear.x + K * msg->angular.z);

    setWheelRpms(wheelRpms);

}




#include <memory>
#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VescNode>());
    rclcpp::shutdown();
    return 0;
}
