#include "leg_move_controller.hpp"
#include <string>
#include <list>
#include <vector>

#ifndef MOVE_MANAGER_HPP
#define MOVE_MANAGER_HPP

using namespace std;


/// @brief Provides access to legs and control legs gaits
class MoveManager
{
private:
    list<LegMoveController> legs;

public:
    MoveManager(void){};
    void set_legs(const list<LegMoveController>& _legs){legs = _legs;};
    LegMoveController get_leg(string id);
    const list<LegMoveController>& get_all_legs(void);
    vector<string> get_all_leg_ids(void);
    void move_leg_to_position(const string& leg_id, std::array<float, 3>& position);
    void move_leg_to_position_normalized(const string& leg_id, std::array<float, 3>& position);
};

#endif