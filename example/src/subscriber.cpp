#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class SimpleSubscriber : public rclcpp::Node{
public:
    SimpleSubscriber() : Node("simple_subscriber"){
        
        subscriber = this->create_subscription<std_msgs::msg::String>(
            "example_topic", 10, std::bind(&SimpleSubscriber::callback, this, _1));
    
    }
private:

    void callback(const std_msgs::msg::String &msg) const{
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;
};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SimpleSubscriber>());
    rclcpp::shutdown();

    return 0;
}