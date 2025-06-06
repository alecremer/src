#ifndef POSE_NODE_HPP
#define POSE_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include "body_publisher.hpp"

using namespace rclcpp;

class PoseNode : public rclcpp::Node{

public:

    PoseNode() : Node("pose_node"){

        

    }

private:

};


#endif // POSE_NODE_HPP