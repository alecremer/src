#ifndef LEG_PUBLISHER_HPP
#define LEG_PUBLISHER_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <memory>
#include "leg_publisher_config.hpp"

using namespace rclcpp;

class LegPublisher {

public:

    LegPublisher(const LegPublisherConfig& topics, Node::SharedPtr node): topics_(topics){
      
        pub_joint_rt_coxar = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_rt_coxa, 10);
        pub_joint_rt_femur = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_rt_femur, 10);
        pub_joint_rt_tibia = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_rt_tibia, 10);
        pub_joint_lf_coxar = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_lt_coxa, 10);
        pub_joint_lf_femur = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_lt_femur, 10);
        pub_joint_lf_tibia = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_lt_tibia, 10);
    
    };

private:

    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_rt_coxar;
    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_rt_femur;
    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_rt_tibia;
    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_lf_coxar;
    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_lf_femur;
    Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_lf_tibia;

    LegPublisherConfig topics_;
};


#endif // LEG_PUBLISHER_HPP