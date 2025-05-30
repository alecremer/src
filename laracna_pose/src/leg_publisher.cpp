#include "laracna_pose/leg_publisher.hpp"
using namespace rclcpp;


LegPublisher::LegPublisher(const LegPublisherConfig& topics, Node::SharedPtr node): topics_(topics){
    
    pub_joint_coxar = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_coxa, 10);
    pub_joint_femur = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_femur, 10);
    pub_joint_tibia = node->create_publisher<std_msgs::msg::Float32>(topics_.topic_joint_tibia, 10);

};
