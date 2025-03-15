#ifndef LEG_PUBLISHERS_HPP
#define LEG_PUBLISHERS_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace rclcpp;

class LegPublishers{

public:
    Publisher<std_msgs::msg::Float64>::SharedPtr coxa;
    Publisher<std_msgs::msg::Float64>::SharedPtr femur;
    Publisher<std_msgs::msg::Float64>::SharedPtr tibia;

    LegPublishers(Publisher<std_msgs::msg::Float64>::SharedPtr coxa, Publisher<std_msgs::msg::Float64>::SharedPtr femur, Publisher<std_msgs::msg::Float64>::SharedPtr tibia){
        this->coxa = coxa;
        this->femur = femur;
        this->tibia = tibia;
    }
    LegPublishers(){}
};

#endif