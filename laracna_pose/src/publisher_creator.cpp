#include <rclcpp/rclcpp.hpp>
#include "laracna_pose/publisher_creator.hpp"

using namespace rclcpp;


PublisherCreator::PublisherCreator(shared_ptr<Node> node){

    LegPublisherConfig leg_rt_config, leg_rb_config, leg_lt_config, leg_lb_config;

    leg_rt_config.topic_joint_coxa  = "/hw_sim/leg_rt/coxa/move";
    leg_rt_config.topic_joint_femur = "/hw_sim/leg_rt/femur/move";
    leg_rt_config.topic_joint_tibia = "/hw_sim/leg_rt/tibia/move";

    leg_rb_config.topic_joint_coxa  = "/hw_sim/leg_rb/coxa/move";
    leg_rb_config.topic_joint_femur = "/hw_sim/leg_rb/femur/move";
    leg_rb_config.topic_joint_tibia = "/hw_sim/leg_rb/tibia/move";

    leg_lt_config.topic_joint_coxa  = "/hw_sim/leg_lt/coxa/move";
    leg_lt_config.topic_joint_femur = "/hw_sim/leg_lt/femur/move";
    leg_lt_config.topic_joint_tibia = "/hw_sim/leg_lt/tibia/move";

    leg_lb_config.topic_joint_coxa  = "/hw_sim/leg_lb/coxa/move";
    leg_lb_config.topic_joint_femur = "/hw_sim/leg_lb/femur/move";
    leg_lb_config.topic_joint_tibia = "/hw_sim/leg_lb/tibia/move";

    leg_rt_publisher = LegPublisher(leg_rt_config, node);
    leg_rb_publisher = LegPublisher(leg_rb_config, node);
    leg_lt_publisher = LegPublisher(leg_lt_config, node);
    leg_lb_publisher = LegPublisher(leg_lb_config, node);

}

