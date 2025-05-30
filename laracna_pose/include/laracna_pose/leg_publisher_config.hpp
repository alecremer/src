#ifndef LEG_PUBLISHER_CONFIG_HPP
#define LEG_PUBLISHER_CONFIG_HPP

#include <string>

using namespace std;


class LegPublisherConfig 
{

public:

    string topic_joint_coxa;
    string topic_joint_femur;
    string topic_joint_tibia;
};


#endif // LEG_PUBLISHER_CONFIG_HPP