#include "laracna_hw_sim/driver_sim.hpp"
#include <functional>

using std::placeholders::_1;

DriverSim::DriverSim(const LegPublishers &leg_publishers): _leg_publishers(leg_publishers){
    

    move_coxa = bind(&DriverSim::move_servo, this, _leg_publishers.coxa, _1);
    move_femur = bind(&DriverSim::move_servo, this, _leg_publishers.femur, _1);
    move_femur = bind(&DriverSim::move_servo, this, _leg_publishers.tibia, _1);
}


DriverSim::DriverSim(): _leg_publishers(LegPublishers()){}

void DriverSim::move_servo(const Publisher<std_msgs::msg::Float64>::SharedPtr &publisher, const float& angle){

    auto message = std_msgs::msg::Float64();
    message.data = angle;
    publisher->publish(message);
    std::cout << "Publishing";
}


