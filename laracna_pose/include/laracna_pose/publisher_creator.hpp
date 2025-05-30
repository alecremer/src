#ifndef PUBLISHER_CREATOR_HPP
#define PUBLISHER_CREATOR_HPP

#include <rclcpp/rclcpp.hpp>
#include "leg_publisher_config.hpp"
#include "laracna_pose/leg_publisher.hpp"

using namespace rclcpp;

class PublisherCreator{

public:

    PublisherCreator(shared_ptr<Node> node);


private:
    LegPublisher leg_rt_publisher;
    LegPublisher leg_rb_publisher;
    LegPublisher leg_lt_publisher;
    LegPublisher leg_lb_publisher;
};

#endif // PUBLISHER_CREATOR_HPP