#ifndef BODY_POSE_HPP
#define BODY_POSE_HPP

#include "leg_pose.hpp"

using namespace std;

class BodyPose {

public:

    BodyPose(void){};
    BodyPose(LegPose leg_rt_ext, LegPose leg_rb_ext, LegPose leg_lt_ext, LegPose leg_lb_ext): 
    leg_rt(leg_rt_ext), leg_rb(leg_rb_ext), leg_lt(leg_lt_ext), leg_lb(leg_lb_ext)
    {};
    BodyPose(LegPose leg_ext): 
    leg_rt(leg_ext), leg_rb(leg_ext), leg_lt(leg_ext), leg_lb(leg_ext)
    {};
    LegPose leg_rt, leg_rb, leg_lt, leg_lb;
    BodyPose rad(void){

        BodyPose pose_rad;
        pose_rad.leg_lb = this->leg_lb.rad();
        pose_rad.leg_lt = this->leg_lt.rad();
        pose_rad.leg_rb = this->leg_rb.rad();
        pose_rad.leg_rt = this->leg_rt.rad();

        return pose_rad;
    }

private:



};

#endif // BODY_POSE_HPP