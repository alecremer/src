#ifndef LEG_PUBLISHER_MAP_HPP
#define LEG_PUBLISHER_MAP_HPP

#include <string>

using namespace std;

/**
 * @brief Names of leg joint topics 
 * 
 */
class LegPublisherMap 
{

public:

    string topic_joint_coxa;
    string topic_joint_femur;
    string topic_joint_tibia;
};


#endif // LEG_PUBLISHER_MAP_HPP