#include <string>
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "laracna_pose/pose_node.hpp"


int main(int argc, char **argv){

    rclcpp::init(argc, argv);


    rclcpp::Node::SharedPtr node_shr = std::make_shared<PoseNode>();
    PublisherCreator pub_creator(node_shr);

    rclcpp::spin(node_shr);
    rclcpp::shutdown();
    return 0;
}