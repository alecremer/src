#ifndef PUBLISHER_CREATOR_HPP
#define PUBLISHER_CREATOR_HPP

#include <rclcpp/rclcpp.hpp>
#include "leg_publisher_config.hpp"
#include "laracna_pose/leg_publisher.hpp"

using namespace rclcpp;

class PublisherCreator{

public:

    PublisherCreator(Node::SharedPtr node);


private:

};

#endif // PUBLISHER_CREATOR_HPP