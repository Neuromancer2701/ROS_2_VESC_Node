#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "minimal_chatter/msg/l_num_m.hpp"

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<minimal_chatter::msg::LNumM>(
      "chatter",
      [this](minimal_chatter::msg::LNumM::UniquePtr msg) {
      RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->num);
    });
  }

private:
  rclcpp::Subscription<minimal_chatter::msg::LNumM>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
