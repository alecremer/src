#ifndef LEG_CONFIG
#define LEG_CONFIG

#include <string>

using namespace std;

/// @brief Leg abstraction
class LegConfig
{
public:
    float coxa_length;
    float femur_length;
    float tibia_length;
    float coxa_angle_offset;
    float femur_angle_offset;
    float tibia_angle_offset;
    string id; // used to access leg by user/robot

    LegConfig(
        float _coxa_length, float _femur_length, float _tibia_length,
        float _coxa_angle_offset, float _femur_angle_offset, float _tibia_angle_offset, 
        string id) : id(id),
        coxa_length(_coxa_length), femur_length(_femur_length), tibia_length(_tibia_length),
        coxa_angle_offset(_coxa_angle_offset), femur_angle_offset(_femur_angle_offset), tibia_angle_offset(_tibia_angle_offset) 
        {};
    LegConfig(void){};
};


#endif