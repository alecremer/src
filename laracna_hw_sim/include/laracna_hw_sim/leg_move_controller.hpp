#ifndef LEG_MOVE_CONTROLLER_HPP
#define LEG_MOVE_CONTROLLER_HPP


#include <array>
#include <iostream>

#include "ik.hpp"
#include "leg_config.hpp"
#include "driver_sim.hpp"
#include "leg_publishers.hpp"

/**
 * @brief Control leg motors
 */
class LegMoveController {
public:
    LegMoveController(const LegConfig& leg_config_ext, const LegPublishers& leg_pub_ext);
    LegMoveController();
    LegMoveController& operator=(const LegMoveController& leg_move_controller){
        if (this != &leg_move_controller) {
            id = leg_move_controller.id;
            coxa_length = leg_move_controller.coxa_length;
            femur_length = leg_move_controller.femur_length;
            tibia_length = leg_move_controller.tibia_length;
            _leg_config = leg_move_controller._leg_config;
            _driver_sim = leg_move_controller._driver_sim;
            // Copiar outros membros, se necessário
        }
        return *this;
    }

    std::string id = "";
    float coxa_length = 0.0f;
    float femur_length = 0.0f;
    float tibia_length = 0.0f;

    /**
     * @brief move leg to position
     * @param position: target of extremity of leg
     */
    void move_to_position(std::array<float, 3>&position);

    /**
     * @brief Moves coxa servo
     * @param angle: angle to move (degrees)
     */
    void move_servo_coxa(const float&angle);

    /**
     * @brief Moves femur servo
     * @param angle: angle to move (degrees)
     */
    void move_servo_femur(const float&angle);

    /**
     * @brief Moves tibia servo
     * @param angle: angle to move (degrees)
     */
    void move_servo_tibia(const float&angle);

    // float read_servo_angle(const string& servo_id);
    // array<float, 3> get_pos_from_angles(void);
    

private:
    IK ik_servo;
    LegConfig _leg_config;
    DriverSim _driver_sim;
    // void move_servo_x(servo_driver&drive, const float&angle);

};


#endif
