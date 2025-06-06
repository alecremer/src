#ifndef MOVE_HPP
#define MOVE_HPP

#include "body_pose.hpp"

using namespace std;

class Move {

public:

    Move(void){};
    Move(BodyPose pose_ext, float t_ext): pose(pose_ext), t(t_ext){};
    BodyPose pose;
    /**
     * @brief t for execute move, in ms
     * 
     */
    float t;

private:

};

#endif // MOVE_HPP