#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "minimal_chatter/msg/l_num_m.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<minimal_chatter::msg::LNumM>("chatter");
    auto timer_callback =
      [this]() -> void {
        auto message = minimal_chatter::msg::LNumM();
        message.num = this->count_++;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.num);
        this->publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(500ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<minimal_chatter::msg::LNumM>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
