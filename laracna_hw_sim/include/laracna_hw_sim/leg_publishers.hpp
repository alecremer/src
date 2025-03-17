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
    // LegPublishers(rclcpp::Node::SharedPtr node, const std::string& coxa_topic, const std::string& femur_topic, const std::string& tibia_topic){
    //     coxa = node->create_publisher<std_msgs::msg::Float64>(coxa_topic, 10);
    //     femur = node->create_publisher<std_msgs::msg::Float64>(femur_topic, 10);
    //     tibia = node->create_publisher<std_msgs::msg::Float64>(tibia_topic, 10);
    // }
    LegPublishers(){}
    // Operador de cópia
    LegPublishers(const LegPublishers& other) 
        : coxa(other.coxa), femur(other.femur), tibia(other.tibia) {}

    // Operador de atribuição por cópia
    LegPublishers& operator=(const LegPublishers& other) {
        if (this != &other) {
            coxa = other.coxa;
            femur = other.femur;
            tibia = other.tibia;
        }
        return *this;
    }
};

#endif