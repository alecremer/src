#include "laracna_hw_sim/move_manager.hpp"
#include <algorithm>

const char* TAG_SERVO_REG = "ServoRegister";
const char* TAG_SERVO_MOVE = "ServoMove";

LegMoveController MoveManager::get_leg(string id){


    list<LegMoveController>::iterator result = std::find_if(legs.begin(), legs.end(), [&id](LegMoveController l){ return (l.id == id);});
    if(result != legs.end())
        return *result;
    else{
        LegMoveController err;
        err.id = "error";
        return err;
    }
}

vector<string> MoveManager::get_all_leg_ids(){
  
  vector<string> leg_ids;
  for(LegMoveController& leg : legs) leg_ids.push_back(leg.id);
  return leg_ids;

} 

const list<LegMoveController>& MoveManager::get_all_legs(){ return legs;}

void MoveManager::move_leg_to_position(const string& leg_id, std::array<float, 3>& position){

    get_leg(leg_id).move_to_position(position);
}

void MoveManager::move_leg_to_position_normalized(const string& leg_id, std::array<float, 3>& position){
    
    LegMoveController leg = get_leg(leg_id);

    // check errors
    for_each(begin(position), end(position), 
        [](float pos){ 
            if(pos < -1 || 1 < pos){

                return;
            }
        }
        );

    // normalized to value
    position[0] *= leg.coxa_length + leg.femur_length + leg.tibia_length;
    position[1] *= leg.femur_length + leg.femur_length + leg.tibia_length;
    position[2] *= leg.tibia_length + leg.femur_length + leg.tibia_length;

    leg.move_to_position(position);

}
