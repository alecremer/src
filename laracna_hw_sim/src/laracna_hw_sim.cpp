#include "laracna_hw_sim/leg_move_controller.hpp"
#include "laracna_hw_sim/leg_publishers.hpp"
#include "laracna_hw_sim/leg_config.hpp"
#include "laracna_hw_sim/move_manager.hpp"
#include <list>
#include <array>

#include "std_msgs/msg/float64_multi_array.hpp"
#include "std_msgs/msg/bool.hpp"
#include "rclcpp/rclcpp.hpp"

// #define COXA_LENGTH 1.0
// #define FEMUR_LENGTH 1.0
// #define TIBIA_LENGTH 1.0
// #define COXA_ANGLE_OFFSET 90.0
// #define FEMUR_ANGLE_OFFSET 90.0
// #define TIBIA_ANGLE_OFFSET 45.0
#define RATE 100

class LaracnaHWSim : public rclcpp::Node{
public:
    LaracnaHWSim(): Node("laracna_hw_sim"){

        this->declare_parameter<double>("coxa_length", 1.0);
        this->declare_parameter<double>("femur_length", 1.0);
        this->declare_parameter<double>("tibia_length", 1.0);
        this->declare_parameter<double>("coxa_angle_offset", 90.0);
        this->declare_parameter<double>("femur_angle_offset", 90.0);
        this->declare_parameter<double>("tibia_angle_offset", 45.0);

        // get params
        coxa_length = get_parameter("coxa_length").as_double();
        femur_length = get_parameter("femur_length").as_double();
        tibia_length = get_parameter("tibia_length").as_double();
        coxa_angle_offset = get_parameter("coxa_angle_offset").as_double();
        femur_angle_offset = get_parameter("femur_angle_offset").as_double();
        tibia_angle_offset = get_parameter("tibia_angle_offset").as_double();

        // populate leg_publishers
        publisher_coxa_move_lt = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_lt/coxa/move", 10);
        publisher_femur_move_lt = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_lt/femur/move", 10);
        publisher_tibia_move_lt = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_lt/tibia/move", 10);

        publisher_coxa_move_rt = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_rt/coxa/move", 10);
        publisher_femur_move_rt = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_rt/femur/move", 10);
        publisher_tibia_move_rt = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_rt/tibia/move", 10);

        publisher_coxa_move_lb = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_lb/coxa/move", 10);
        publisher_femur_move_lb = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_lb/femur/move", 10);
        publisher_tibia_move_lb = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_lb/tibia/move", 10);

        publisher_coxa_move_rb = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_rb/coxa/move", 10);
        publisher_femur_move_rb = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_rb/femur/move", 10);
        publisher_tibia_move_rb = this->create_publisher<std_msgs::msg::Float64>("/hw_sim/leg_rb/tibia/move", 10);

        leg_rt_publishers = LegPublishers(publisher_coxa_move_rt, publisher_femur_move_rt, publisher_tibia_move_rt);
        leg_lt_publishers = LegPublishers(publisher_coxa_move_lt, publisher_femur_move_lt, publisher_tibia_move_lt);
        leg_lb_publishers = LegPublishers(publisher_coxa_move_lb, publisher_femur_move_lb, publisher_tibia_move_lb);
        leg_rb_publishers = LegPublishers(publisher_coxa_move_rb, publisher_femur_move_rb, publisher_tibia_move_rb);
        

        // create leg config 

        leg_config_lt = LegConfig(coxa_length, femur_length, tibia_length, coxa_angle_offset, femur_angle_offset, tibia_angle_offset, "leg_lt");
        leg_config_rt = LegConfig(coxa_length, femur_length, tibia_length, coxa_angle_offset, femur_angle_offset, tibia_angle_offset, "leg_rt");
        leg_config_lb = LegConfig(coxa_length, femur_length, tibia_length, coxa_angle_offset, femur_angle_offset, tibia_angle_offset, "leg_lb");
        leg_config_rb = LegConfig(coxa_length, femur_length, tibia_length, coxa_angle_offset, femur_angle_offset, tibia_angle_offset, "leg_rb");

        // leg_config_lt = LegConfig(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, COXA_ANGLE_OFFSET, FEMUR_ANGLE_OFFSET, TIBIA_ANGLE_OFFSET, "leg_lt");
        // leg_config_rt = LegConfig(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, COXA_ANGLE_OFFSET, FEMUR_ANGLE_OFFSET, TIBIA_ANGLE_OFFSET, "leg_rt");
        // leg_config_lb = LegConfig(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, COXA_ANGLE_OFFSET, FEMUR_ANGLE_OFFSET, TIBIA_ANGLE_OFFSET, "leg_lb");
        // leg_config_rb = LegConfig(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, COXA_ANGLE_OFFSET, FEMUR_ANGLE_OFFSET, TIBIA_ANGLE_OFFSET, "leg_rb");

        // create leg move controller

        leg_lt_move_controller = LegMoveController(leg_config_lt, leg_lt_publishers);
        leg_rt_move_controller = LegMoveController(leg_config_rt, leg_rt_publishers);
        leg_lb_move_controller = LegMoveController(leg_config_lb, leg_lb_publishers);
        leg_rb_move_controller = LegMoveController(leg_config_rb, leg_rb_publishers);

        list<LegMoveController> legs = {leg_lt_move_controller, leg_rt_move_controller, leg_lb_move_controller, leg_rb_move_controller}; 
        move_manager.set_legs(legs);

        subscriber_leg_lb = this->create_subscription<std_msgs::msg::Float64MultiArray>("/move_manager/leg_lb/position", 10, 
                                                    [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg){
                                                        this->leg_lb_pos_ros = {(float)  msg->data[0], (float)  msg->data[1], (float)  msg->data[2]};
                                                        });

        subscriber_leg_lt = this->create_subscription<std_msgs::msg::Float64MultiArray>("/move_manager/leg_lt/position", 10, 
                                                    [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg){
                                                        this->leg_lt_pos_ros = {(float)  msg->data[0], (float)  msg->data[1], (float)  msg->data[2]};
                                                        });
        

        subscriber_leg_rt = this->create_subscription<std_msgs::msg::Float64MultiArray>("/move_manager/leg_rt/position", 10, 
                                                    [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg){
                                                        this->leg_rt_pos_ros = {(float) (float)  msg->data[0], (float)  msg->data[1], (float)  msg->data[2]};
                                                        });

        subscriber_leg_rb = this->create_subscription<std_msgs::msg::Float64MultiArray>("/move_manager/leg_rb/position", 10, 
                                                    [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg){
                                                        this->leg_rb_pos_ros = {(float)  msg->data[0], (float)  msg->data[1], (float)  msg->data[2]};
                                                        });

        subscriber_use_move_position = this->create_subscription<std_msgs::msg::Bool>("/move_manager/param/use_move_position", 10, 
                                                    [this](const std_msgs::msg::Bool::SharedPtr msg){
                                                        this->use_move_position = msg->data;
                                                        });

        // create subscribers
        // subscriber_lb = this->create_subscription<std_msgs::msg::Float64>("/move_manager/leg_lb/angle", 10, 
        //                                             [this](const std_msgs::msg::Float64::SharedPtr &msg){this->leg_lb_angle_ros = msg->data;});
        // subscriber_lt = this->create_subscription<std_msgs::msg::Float64>("/move_manager/leg_lt/angle", 10, 
        //                                             [this](const std_msgs::msg::Float64::SharedPtr &msg){this->leg_lt_angle_ros = msg->data;});
        // subscriber_rt = this->create_subscription<std_msgs::msg::Float64>("/move_manager/leg_rt/angle", 10, 
        //                                             [this](const std_msgs::msg::Float64::SharedPtr &msg){this->leg_rt_angle_ros = msg->data;});
        // subscriber_rb = this->create_subscription<std_msgs::msg::Float64>("/move_manager/leg_rb/angle", 10, 
        //                                             [this](const std_msgs::msg::Float64::SharedPtr &msg){this->leg_rb_angle_ros = msg->data;});

    }

    void get_multiarray(const std_msgs::msg::Float64MultiArray &msg, list<float> &leg_ros){
        leg_ros = {(float) msg.data[0], (float) msg.data[1], (float) msg.data[2]};
    }
    void run(){

        auto rate = Rate(RATE);
        
        while (ok())
        {
            spin_some(this->get_node_base_interface());

            // leg_lb_angle = leg_lb_angle_ros;
            // leg_lt_angle = leg_lt_angle_ros;
            // leg_rt_angle = leg_rt_angle_ros;
            // leg_rb_angle = leg_rb_angle_ros;

            leg_lb_pos = leg_lb_pos_ros;
            leg_lt_pos = leg_lt_pos_ros;
            leg_rt_pos = leg_rt_pos_ros;
            leg_rb_pos = leg_rb_pos_ros;

            move_manager.move_leg_to_position(leg_config_lb.id, leg_lb_pos);
            // rate.sleep();
            
            move_manager.move_leg_to_position(leg_config_lt.id, leg_lt_pos);
            // rate.sleep();
            
            move_manager.move_leg_to_position(leg_config_rt.id, leg_rt_pos);
            // rate.sleep();

            move_manager.move_leg_to_position(leg_config_rb.id, leg_rb_pos);
            rate.sleep();


        }

    }
private:

    float coxa_length = 0.0f;
    float femur_length = 0.0f;
    float tibia_length = 0.0f;

    float coxa_angle_offset = 0.0f;
    float femur_angle_offset = 0.0f;
    float tibia_angle_offset = 0.0f;

    LegPublishers leg_lt_publishers;
    LegPublishers leg_rt_publishers;
    LegPublishers leg_lb_publishers;
    LegPublishers leg_rb_publishers;

    LegMoveController leg_lt_move_controller;
    LegMoveController leg_rt_move_controller;
    LegMoveController leg_lb_move_controller;
    LegMoveController leg_rb_move_controller;

    LegConfig leg_config_lt;
    LegConfig leg_config_rt;
    LegConfig leg_config_lb;
    LegConfig leg_config_rb;

    MoveManager move_manager;

    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_coxa_move_lt;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_femur_move_lt;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_tibia_move_lt;

    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_coxa_move_rt;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_femur_move_rt;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_tibia_move_rt;

    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_coxa_move_lb;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_femur_move_lb;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_tibia_move_lb;

    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_coxa_move_rb;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_femur_move_rb;
    Publisher<std_msgs::msg::Float64>::SharedPtr publisher_tibia_move_rb;

    Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscriber_leg_lt;
    Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscriber_leg_lb;
    Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscriber_leg_rt;
    Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscriber_leg_rb;

    Subscription<std_msgs::msg::Bool>::SharedPtr subscriber_use_move_position;

    array<float, 3> leg_lb_pos = {0, 0, 0};
    array<float, 3> leg_lt_pos = {0, 0, 0};
    array<float, 3> leg_rb_pos = {0, 0, 0};
    array<float, 3> leg_rt_pos = {0, 0, 0};

    array<float, 3> leg_lb_pos_ros = {0, 0, 0};
    array<float, 3> leg_lt_pos_ros = {0, 0, 0};
    array<float, 3> leg_rb_pos_ros = {0, 0, 0};
    array<float, 3> leg_rt_pos_ros = {0, 0, 0};

    bool use_move_position = true;

    // rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber_lt;
    // rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber_lb;
    // rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber_rt;
    // rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber_rb;

    // float leg_lt_angle = 0;
    // float leg_lb_angle = 0;
    // float leg_rt_angle = 0;
    // float leg_rb_angle = 0;

    // float leg_lt_angle_ros = 0;
    // float leg_lb_angle_ros = 0;
    // float leg_rt_angle_ros = 0;
    // float leg_rb_angle_ros = 0;

};


int main(int argc, char **argv){
    
    std::cout << "Start";

    init(argc, argv);
    auto node = make_shared<LaracnaHWSim>();
    node->run();
    shutdown();

    std::cout << "Dying";


    return 0;

}
