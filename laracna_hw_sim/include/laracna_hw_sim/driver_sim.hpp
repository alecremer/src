#ifndef DRIVER_SIM_HPP
#define DRIVER_SIM_HPP

#include <vector>
#include <array>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/float64.hpp"
#include "leg_publishers.hpp"

using namespace std;
using namespace rclcpp;

class DriverSim{
    public:
        
        DriverSim(const LegPublishers& leg_publishers);
        DriverSim(void);

        void move_servo(const Publisher<std_msgs::msg::Float64>::SharedPtr &publisher, const float& angle);
        std::function<void(const float&)> move_coxa;
        std::function<void(const float&)> move_femur;
        std::function<void(const float&)> move_tibia;

    private:

        LegPublishers _leg_publishers;
};

#endif