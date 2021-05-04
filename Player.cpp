#include "Player.hpp"
#include <string>

namespace pandemic{


    Player::Player(Board &bo ,City st_city) : board(bo) , start_city(st_city){}
    Player::Player(Board &bo ,City st_city , int i) : board(bo) , start_city(st_city){}

    City &start_city(City);

    Player &Player::drive(City){
        return *this;
    }

    Player &Player::fly_direct(City){
        return *this;
    }

    Player &Player::fly_charter(City){
        return *this;
    }
    
    Player &Player::fly_shuttle(City){
        return *this;
    }

    Player &Player::treat(City){
        return *this;
    }

    Player &Player::build(){
        return *this;
    }

    Player &Player::discover_cure(Color){
        return *this;
    }

    Player Player::take_card(City){
        return *this;
    }

    string Player::role(){
        return "reasearch";
    }
}