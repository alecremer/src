#ifndef LEG_PUBLISHER_HPP
#define LEG_PUBLISHER_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <memory>
#include "leg_publisher_config.hpp"

using namespace rclcpp;

class LegPublisher {

public:

    LegPublisher(const LegPublisherConfig& topics, shared_ptr<Node> node);
    LegPublisher(void){};
private:

    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_coxar;
    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_femur;
    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_tibia;

    LegPublisherConfig topics_;
};


#endif // LEG_PUBLISHER_HPP