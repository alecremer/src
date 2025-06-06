#ifndef CHOREOGRAPHY_HPP
#define CHOREOGRAPHY_HPP

#include <vector>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include "move.hpp"
#include "body_publisher.hpp"

using namespace std;

class ChoreographyPublisher{

public:

    ChoreographyPublisher(BodyPublisher& body_publisher): body_publisher_(body_publisher){}
    void play(vector<Move> choreography){
        for(auto move : choreography){
            body_publisher_.pub(move.pose);
            rclcpp::sleep_for(chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::duration<double>(move.t*1000)
            ));
        }
    }

private:

    BodyPublisher body_publisher_;

};


#endif // CHOREOGRAPHY_HPP
