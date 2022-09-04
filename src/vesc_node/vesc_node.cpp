
#include "vesc_node.hpp"
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include <rcutils/logging_macros.h>

namespace{
    using std::placeholders::_1;
    using namespace std::chrono_literals;
    using std::mutex;
    using std::map;
    using std::lock_guard;
}



VescNode::VescNode():Node("vesc_pub_sub"), counter(0)
{
    RCUTILS_LOG_INFO("%s ", __PRETTY_FUNCTION__);
    onInit();
}

void VescNode::onInit()
{
    vescApi.FindandMapMotorControllers();

    if(vescApi.isTwoWheelDrive())
    {
        RCUTILS_LOG_INFO("Found all required wheels");
        publisher_ =    this->create_publisher<MotorData>("motor_data", 10);
        pub_timer_ =    this->create_wall_timer( 20ms, std::bind(&VescNode::timer_callback, this));
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", rclcpp::QoS(10), std::bind(&VescNode::twist_callback, this, _1));
    }
    else
    {
           RCUTILS_LOG_INFO("Could not find all required wheels");
    }

}


unordered_map<int, int> VescNode::getWheelRpms()
{
    lock_guard<std::mutex> lock(rpm_mutex);
    return wheel_rpms;
}

void VescNode::setWheelRpms(const unordered_map<int, int> &wheelRpms)
{
    lock_guard<std::mutex> lock(rpm_mutex);
    wheel_rpms = wheelRpms;
}

void VescNode::timer_callback()
{

    auto wheelRpms = getWheelRpms();

    RCUTILS_LOG_INFO("timer_callback:left rpm %d right rpm:%d",
                     wheelRpms[vesc::Vesc::left_back], wheelRpms[vesc::Vesc::right_back]);
    vescApi.SetWheelsRPM(wheelRpms);

    if(++counter > PUB_INTERVAL)
    {
        //TODO vescApi.getMotorData;
        auto message = MotorData();
        message.current  = 1.235;
        message.speed    = 2.456;
        message.voltage  = 39.78;
        //RCUTILS_LOG_INFO( "Publisher: '%s'", message.data.c_str());
        publisher_->publish(message);
        counter = 0;
    }

}

void VescNode::twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
{

    auto w_L{msg->angular.z * L_m};
    auto scaledVelocity_m_per_s{msg->linear.x * V_MAX_m_per_s * 2.0};

    auto Velocity_right_m_per_s {((scaledVelocity_m_per_s + w_L)/DIAMETER_m)};
    auto Velocity_left_m_per_s {((scaledVelocity_m_per_s - w_L)/DIAMETER_m)};

    unordered_map<int, int> wheelRpms;
    wheelRpms[vesc::Vesc::right_back] = static_cast<int>(m_per_sec_convert_RPM * Velocity_right_m_per_s);
    wheelRpms[vesc::Vesc::left_back]  = static_cast<int>(m_per_sec_convert_RPM * Velocity_left_m_per_s);

    RCUTILS_LOG_INFO("Twist callback:left rpm %d right rpm:%d",
                     wheelRpms[vesc::Vesc::left_back], wheelRpms[vesc::Vesc::right_back]);
    setWheelRpms(wheelRpms);

}






int main(int argc, char * argv[])
{
    RCUTILS_LOG_INFO("VESC Node startup");
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VescNode>());
    rclcpp::shutdown();
    return 0;
}
