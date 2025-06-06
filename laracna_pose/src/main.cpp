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


void play_intial_pose(ChoreographyPublisher& choreography_pub){

    Vector3<float> zero_vector{0};
    LegPose zero_pose(zero_vector);
    BodyPose intial_pose(zero_pose);
    Move move(intial_pose, 3000);
    choreography_pub.play(vector<Move>{move});

}

void play_wakeup_pose(ChoreographyPublisher& choreography_pub){

    LegPose prepare_for_force_pose;
    prepare_for_force_pose.set_coxa(0);
    prepare_for_force_pose.set_femur(60);
    prepare_for_force_pose.set_tibia(45);

    BodyPose prepare_pose(prepare_for_force_pose);

    Move move(prepare_pose, 3000);
    choreography_pub.play(vector<Move>{move});

}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);


    rclcpp::Node::SharedPtr node_shr = std::make_shared<PoseNode>();
    BodyPublisher body_pub(node_shr);
    ChoreographyPublisher choreography_pub(body_pub);

    initial_pose_sub = node_shr->create_subscription<std_msgs::msg::Bool>(
            "inital_pose", 10, [&choreography_pub](const std_msgs::msg::Bool::SharedPtr msg){
                play_intial_pose(choreography_pub);
            }
        );

    wakeup_sub = node_shr->create_subscription<std_msgs::msg::Bool>(
        "wakeup_pose", 10, [&choreography_pub](const std_msgs::msg::Bool::SharedPtr msg){
            cout << "Its works??" << endl;
            play_wakeup_pose(choreography_pub);
        }
    );

    rclcpp::spin(node_shr);
    rclcpp::shutdown();
    return 0;
}