#include <string>
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class SimplePublisher : public rclcpp::Node{
public:
    SimplePublisher() : Node("simple_publisher"){
        publisher_obj = this->create_publisher<std_msgs::msg::String>("example_topic", 20); // buffer size 20

        // interval between trigger callbacks
        timer = this->create_wall_timer(1s, std::bind(&SimplePublisher::callback_function, this));
    }
private:
    int counter = 0;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_obj;
    void callback_function(){
        counter++;
        auto message = std_msgs::msg::String();
        message.data = "Hello World " + std::to_string(counter);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_obj->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer;

};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SimplePublisher>());
    rclcpp::shutdown();
    return 0;
}