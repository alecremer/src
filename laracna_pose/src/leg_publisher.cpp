#include "laracna_pose/leg_publisher.hpp"
using namespace rclcpp;


LegPublisher::LegPublisher(const LegPublisherMap& topics, std::shared_ptr<Node> node): leg_pub_config_(topics){
    
    pub_joint_coxa = node->create_publisher<std_msgs::msg::Float64>(leg_pub_config_.topic_joint_coxa, 10);
    pub_joint_femur = node->create_publisher<std_msgs::msg::Float64>(leg_pub_config_.topic_joint_femur, 10);
    pub_joint_tibia = node->create_publisher<std_msgs::msg::Float64>(leg_pub_config_.topic_joint_tibia, 10);

}


void LegPublisher::pub(LegPose& leg_pose){
    
    std_msgs::msg::Float64 msg;
    
    msg.data = leg_pose.get_coxa();
    (*pub_joint_coxa).publish(msg);
    
    msg.data = leg_pose.get_femur();
    (*pub_joint_femur).publish(msg);
    
    msg.data = leg_pose.get_tibia();
    (*pub_joint_tibia).publish(msg);

}