#pragma once
#include <iostream>
#include<map>
#include <set>
#include "City.hpp"
#include "Color.hpp"
using namespace std;




namespace pandemic{


    class Board
    {

        //cons
        static map<City,set<City>> myMap;
        static map<City,int> dis_level;
        static map<City,Color> city_color;


        public:
        Board();
        int &operator[](City city);
        const int operator[](City city) const;
        friend ostream& operator << (ostream& os , const Board& bd);
        bool is_clean();
        void remove_cures();

        //des
        ~Board(){};

    };



}