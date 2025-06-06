#ifndef LEG_POSE_HPP
#define LEG_POSE_HPP

#include "vector3.hpp"

using namespace std;

class LegPose {
    
public:

    LegPose(void){};
    LegPose(Vector3<float>& vector_ext): angles(vector_ext){};
    LegPose(float& coxa_angle_ext, float& femur_angle_ext, float& tibia_angle_ext): 
    angles(vector<float>{coxa_angle_ext, femur_angle_ext, tibia_angle_ext}){}

    LegPose& operator=(const Vector3<float>& v_ext){
        angles = v_ext;
        return *this;
    }

    Vector3<float> get_angles(void){
        return angles;
    }

    float get_coxa(void){ return angles.x;};
    float get_femur(void){ return angles.y;};
    float get_tibia(void){ return angles.z;};

    void set_coxa(const float& angle) { angles.x = angle;};
    void set_femur(const float& angle){ angles.y = angle;};
    void set_tibia(const float& angle){ angles.z = angle;};
    
    void reset(void){
        angles = 0;
    }

    LegPose rad(void){
        Vector3<float> angles_rad = this->angles.rad();
        return LegPose(angles_rad);
    }

    LegPose degrees(void){
        Vector3<float> angles_degrees = this->angles.degrees();
        return LegPose(angles_degrees);
    }
    
private:

    Vector3<float> angles;

};

#endif // LEG_POSE_HPP