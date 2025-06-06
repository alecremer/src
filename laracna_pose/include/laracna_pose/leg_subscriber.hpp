// #ifndef LEG_SUBSCRIBER_HPP
// #define LEG_SUBSCRIBER_HPP

// #include <rclcpp/rclcpp.hpp>
// #include <std_msgs/msg/float32.hpp>
// #include <memory>
// #include "leg_subscriber_map.hpp"

// using namespace rclcpp;

// /**
//  * @brief Using some node and config, create publishers of legs 
//  * 
//  */
// class LegSubscriber {

// public:

//     /**
//      * @brief Construct a new Leg Publisher object
//      * 
//      * @param leg_sub_config 
//      * @param node base node
//      */
//     LegSubscriber(const LegSubscriber& leg_sub_config, shared_ptr<Node> node);
//     LegSubscriber(void){};
// private:

//     Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_coxa;
//     Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_femur;
//     Publisher<std_msgs::msg::Float32>::SharedPtr pub_joint_tibia;

//     LegPublisherMap leg_pub_config_;
// };


// #endif // LEG_SUBSCRIBER_HPP