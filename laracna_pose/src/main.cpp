#include <string>
#include <chrono>
#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

#include "laracna_pose/pose_node.hpp"
#include "laracna_pose/choreography_publisher.hpp"
#include "laracna_pose/move.hpp"
#include "laracna_pose/body_pose.hpp"
#include "laracna_pose/leg_pose.hpp"
#include "laracna_pose/vector3.hpp"

rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr initial_pose_sub;
rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr wakeup_sub;

bool debug = true;

float wakeup_1_c = 0.0f;
float wakeup_1_f = 0.0f;
float wakeup_1_t = 0.0f;
float wakeup_1_t_ms = 1000.0f;

float wakeup_2_c = 0.0f;
float wakeup_2_f = 0.0f;
float wakeup_2_t = 0.0f;
float wakeup_2_t_ms = 1000.0f;

void play_initial_pose(ChoreographyPublisher& choreography_pub){

    Vector3<float> zero_vector{0.0f};
    LegPose zero_pose(zero_vector);
    BodyPose intial_pose(zero_pose);
    Move move(intial_pose, 3000);
    choreography_pub.play(vector<Move>{move});
    cout << "initial pose" << endl;
    
}

void play_wakeup_pose(ChoreographyPublisher& choreography_pub){

    LegPose prepare_for_force_pose;
    LegPose force_pose;

    prepare_for_force_pose.set_coxa(wakeup_1_c);
    prepare_for_force_pose.set_femur(wakeup_1_f);
    prepare_for_force_pose.set_tibia(wakeup_1_t);

    force_pose.set_coxa(wakeup_2_c);
    force_pose.set_femur(wakeup_2_f);
    force_pose.set_tibia(wakeup_2_t);


    vector<Move> wakeup_choreography;
    Move move_1(prepare_for_force_pose.rad(), wakeup_1_t_ms);
    Move move_2(force_pose.rad(), wakeup_2_t_ms);
    
    // BodyPose force_legs_lt_rt(force_pose, prepare_for_force_pose, force_pose, prepare_for_force_pose);
    // Move move_2(force_legs_lt_rt.rad(), wakeup_2_t_ms);
    
    // BodyPose force_legs_lb_rb(force_pose);
    // Move move_3(force_legs_lb_rb.rad(), wakeup_2_t_ms);

    wakeup_choreography.push_back(move_1);
    wakeup_choreography.push_back(move_2);
    // wakeup_choreography.push_back(move_3);

    choreography_pub.play(wakeup_choreography);
    cout << "wakeup pose" << endl;

}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);


    rclcpp::Node::SharedPtr node_shr = std::make_shared<PoseNode>();
    BodyPublisher body_pub(node_shr);
    ChoreographyPublisher choreography_pub(body_pub);

    node_shr->declare_parameter<float>("wakeup_1_c", 0.0f);
    node_shr->declare_parameter<float>("wakeup_1_f", 0.0f);
    node_shr->declare_parameter<float>("wakeup_1_t", 0.0f);
    node_shr->declare_parameter<float>("wakeup_1_t_ms", 0.0f);

    node_shr->declare_parameter<float>("wakeup_2_c", 0.0f);
    node_shr->declare_parameter<float>("wakeup_2_f", 0.0f);
    node_shr->declare_parameter<float>("wakeup_2_t", 0.0f);
    node_shr->declare_parameter<float>("wakeup_2_t_ms", 0.0f);


    node_shr->get_parameter("wakeup_1_c", wakeup_1_c);
    node_shr->get_parameter("wakeup_1_f", wakeup_1_f);
    node_shr->get_parameter("wakeup_1_t", wakeup_1_t);
    node_shr->get_parameter("wakeup_1_t_ms", wakeup_1_t_ms);
    
    node_shr->get_parameter("wakeup_2_c", wakeup_2_c);
    node_shr->get_parameter("wakeup_2_f", wakeup_2_f);
    node_shr->get_parameter("wakeup_2_t", wakeup_2_t);
    node_shr->get_parameter("wakeup_2_t_ms", wakeup_2_t_ms);

    initial_pose_sub = node_shr->create_subscription<std_msgs::msg::Bool>(
            "initial_pose", 10, [&choreography_pub](const std_msgs::msg::Bool::SharedPtr msg){
                play_initial_pose(choreography_pub);
            }
        );

    wakeup_sub = node_shr->create_subscription<std_msgs::msg::Bool>(
        "wakeup_pose", 10, [&choreography_pub](const std_msgs::msg::Bool::SharedPtr msg){
            cout << "Its works??" << endl;
            // if(debug){
            //     node_shr->get_parameter("wakeup_1_c", wakeup_1_c);
            //     node_shr->get_parameter("wakeup_1_f", wakeup_1_f);
            //     node_shr->get_parameter("wakeup_1_t", wakeup_1_t);
            // }
            play_wakeup_pose(choreography_pub);
        }
    );

    rclcpp::spin(node_shr);
    rclcpp::shutdown();
    return 0;
}