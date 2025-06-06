#ifndef BODY_PUBLISHER_HPP
#define BODY_PUBLISHER_HPP

#include <rclcpp/rclcpp.hpp>
#include "leg_publisher_map.hpp"
#include "laracna_pose/leg_publisher.hpp"
#include "body_pose.hpp"

using namespace rclcpp;

class BodyPublisher{

public:

    BodyPublisher(shared_ptr<Node> node);
    void pub(BodyPose& body_pose);

private:
    LegPublisher leg_rt_publisher;
    LegPublisher leg_rb_publisher;
    LegPublisher leg_lt_publisher;
    LegPublisher leg_lb_publisher;
};

#endif // BODY_PUBLISHER_HPP