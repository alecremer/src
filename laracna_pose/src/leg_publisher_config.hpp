#ifndef LEG_PUBLISHER_CONFIG_HPP
#define LEG_PUBLISHER_CONFIG_HPP

#include "string.hpp"

using namespace std;


class LegPublisherConfig 
{

public:

    string topic_joint_rt_coxa;
    string topic_joint_rt_femur;
    string topic_joint_rt_tibia;

    string topic_joint_rb_coxa;
    string topic_joint_rb_femur;
    string topic_joint_rb_tibia;

    string topic_joint_lt_coxa;
    string topic_joint_lt_femur;
    string topic_joint_lt_tibia;

    string topic_joint_lb_coxa;
    string topic_joint_lb_femur;
    string topic_joint_lb_tibia;


};


#endif // LEG_PUBLISHER_CONFIG_HPP