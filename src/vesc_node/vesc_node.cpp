//
// Created by root on 6/25/19.
//

#include "vesc_node.h"

vesc_node::vesc_node() : Node("vesc_node")
{
    publisher_ = this->create_publisher<MotorData>("topic", 10);
    pub_timer_ = this->create_wall_timer( 50ms, std::bind(&vesc_node::timer_callback, this));
    subscription_ = create_subscription<Twist>("topic", 10, std::bind(&vesc_node::twist_callback, this, _1));
}


void vesc_node::timer_callback()
{


    if(counter++ > PUB_INTERVAL)
    {
        auto message = MotorData();
        message.current  = 1.235;
        message.speed    = 2.456;
        message.voltage  = 39.78;
        //RCLCPP_INFO(this->get_logger(), "Publisher: '%s'", message.data.c_str());
        publisher_->publish(message);
        counter = 0;
    }
}

void vesc_node::twist_callback(Twist msg)
{

}
