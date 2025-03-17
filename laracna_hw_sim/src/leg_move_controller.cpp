//
//  Create by Ale - 1/8/23
//
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include "laracna_hw_sim/math_utils.hpp"
#include "laracna_hw_sim/ik.hpp"
#include "laracna_hw_sim/leg_move_controller.hpp"


using namespace std;

LegMoveController::LegMoveController(const LegConfig& leg_config_ext, const LegPublishers& leg_pub_ext): _driver_sim(leg_pub_ext), _leg_config(leg_config_ext){
    // _leg_config = leg_config_ext;
    id = _leg_config.id;
    coxa_length = _leg_config.coxa_length;
    femur_length = _leg_config.femur_length;
    tibia_length = _leg_config.tibia_length;
    
}

LegMoveController::LegMoveController() : _driver_sim(){}


void LegMoveController::move_to_position(std::array<float, 3>& position){


    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, coxa_length, femur_length, tibia_length);


    float coxa_angle = servo_angles.at(0) + MathUtils::degToRad(_leg_config.coxa_angle_offset);
    float femur_angle = servo_angles.at(1) + MathUtils::degToRad(_leg_config.femur_angle_offset);
    float tibia_angle = servo_angles.at(2) + MathUtils::degToRad(_leg_config.tibia_angle_offset);

    coxa_angle = MathUtils::simplify_angle_rad(coxa_angle);
    femur_angle = MathUtils::simplify_angle_rad(femur_angle);
    tibia_angle = MathUtils::simplify_angle_rad(tibia_angle);
    
    
    bool coxa_angle_ok = (0 <= coxa_angle && coxa_angle <= M_PI);
    bool femur_angle_ok = (0 <= femur_angle && femur_angle <= M_PI);
    bool tibia_angle_ok = (0 <= tibia_angle && tibia_angle <= M_PI);
    
    
    if(coxa_angle_ok && femur_angle_ok && tibia_angle_ok){

        move_servo_coxa(coxa_angle);
        move_servo_femur(femur_angle);
        move_servo_tibia(tibia_angle);
        
        string m = "Rad: " + to_string(coxa_angle) + ", " + to_string(femur_angle) + ", " + to_string(tibia_angle);
        std::cout << "angle: " << m << std::endl;
        m = "degrees: " + to_string(MathUtils::radToDeg(coxa_angle)) + ", " + to_string(MathUtils::radToDeg(femur_angle)) + ", " + to_string(MathUtils::radToDeg(tibia_angle));
        std::cout << "angle: " << m << std::endl;
    }
    else{

    }

}

void LegMoveController::move_servo_coxa(const float &angle){ 
    _driver_sim.move_coxa(angle);
    }
void LegMoveController::move_servo_femur(const float &angle){ _driver_sim.move_femur(angle);}
void LegMoveController::move_servo_tibia(const float &angle){ _driver_sim.move_tibia(angle);}



// void leg_move_controller::move_servo_x(servo_driver &_drive, const float &_angle){

//     int angle_int = (int) _angle; 
//     _drive.Move(angle_int);

// }


// array<float, 3> leg_move_controller::get_pos_from_angles(){

//     array<float, 3> angles_d{read_servo_angle("c"), read_servo_angle("f"), read_servo_angle("t")};
//     array<float, 3> angles = MathUtils::deg2rad_array(angles_d);
//     array<float, 3> pos;
    
//     float xy_footprint = _leg_config.coxa_length + _leg_config.femur_length*cos(angles[1] + MathUtils::degToRad(_leg_config.femur_angle_offset)) + _leg_config.tibia_length*cos(angles[2] + MathUtils::degToRad(_leg_config.tibia_angle_offset));
    
//     pos[0] = xy_footprint * cos(angles[0] + MathUtils::degToRad(_leg_config.coxa_angle_offset));
//     pos[1] = xy_footprint * sin(angles[0] + MathUtils::degToRad(_leg_config.coxa_angle_offset));
//     pos[2] = _leg_config.femur_length * sin(angles[1] + MathUtils::degToRad(_leg_config.femur_angle_offset)) - _leg_config.tibia_length * sin(angles[2] + MathUtils::degToRad(_leg_config.tibia_angle_offset));

//     return pos;
// }

// float leg_move_controller::read_servo_angle(const string& servo_id){
    
//     // select servo
//     int servo_idx = _leg_config.coxa_ledc_channel; // default coxa == 'c'
//     if(servo_id == "f") servo_idx = _leg_config.femur_ledc_channel;
//     else if(servo_id == "t") servo_idx = _leg_config.tibia_ledc_channel;

//     return _servo_driver.read_servo(servo_idx);

// }

