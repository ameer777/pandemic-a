#pragma once
#include "Board.hpp"

namespace pandemic{
    
    class Player{


        public:
        City start_city;
        set<City> cards;
        Board board; 

        Player(Board &, City);
        Player(Board &,City,int);

        Player &drive(City);
        Player &fly_direct(City);
        Player &fly_charter(City);
        Player &fly_shuttle(City);
        Player &treat(City);

        Player &build();
        

        Player &discover_cure(Color);

        string role();
        Player take_card(City);

    };
}