#ifndef LEG_PUBLISHER_HPP
#define LEG_PUBLISHER_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <memory>
#include "leg_publisher_map.hpp"
#include "leg_pose.hpp"

using namespace rclcpp;

/**
 * @brief Using some node and config, create publishers of legs 
 * 
 */
class LegPublisher {

public:

    /**
     * @brief Construct a new Leg Publisher object
     * 
     * @param leg_pub_config 
     * @param node base node
     */
    LegPublisher(const LegPublisherMap& leg_pub_config, shared_ptr<Node> node);
    LegPublisher(void){};
    void pub(LegPose& leg_pose);

private:

    Publisher<std_msgs::msg::Float64>::SharedPtr pub_joint_coxa;
    Publisher<std_msgs::msg::Float64>::SharedPtr pub_joint_femur;
    Publisher<std_msgs::msg::Float64>::SharedPtr pub_joint_tibia;

    LegPublisherMap leg_pub_config_;
};


#endif // LEG_PUBLISHER_HPP