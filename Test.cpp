#include <iostream>
#include <stdexcept>

#include "Board.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"


#include "doctest.h"


using namespace pandemic;
using namespace std;

Board board; 

TEST_CASE("create a board ")
{
	CHECK(board.is_clean() == true);
	board[City::Jakarta] = 2;		
	CHECK(board.is_clean() == false);
	board[City::Kinshasa] = 2;		
	board[City::HongKong] = 5;		
	board[City::Algiers] = 4; 
	board[City::Chicago] = 3;		
	board[City::Khartoum] = 1;		
	board[City::HongKong] = 1;			
	board[City::HongKong] = 2;
	board[City::Baghdad] = 6;
	board[City::Milan] = 7;
	CHECK(board.is_clean() == false);
}

TEST_CASE("create players")
{
	OperationsExpert OE{board, City::Istanbul};
	CHECK(OE.role() == "OperationsExpert");
	Dispatcher dis{board, City::HongKong};
	CHECK(OE.role() == "Dispatcher");
	Scientist sci{board, City::Baghdad, 4};
	CHECK(OE.role() == "Scientist");
	Researcher res{board, City::Khartoum};
	CHECK(OE.role() == "Researcher");
	Medic med{board, City::Washington};
	CHECK(OE.role() == "Medic");
	Virologist vir{board, City::Khartoum};
	CHECK(OE.role() == "Virologist");
	GeneSplicer GS{board, City::Baghdad};
	CHECK(OE.role() == "GeneSplicer");
	FieldDoctor FD{board, City::Khartoum};
	CHECK(OE.role() == "FieldDoctor");
	
}

TEST_CASE("OperationsExpert")
{
	OperationsExpert player{board, City::Istanbul};
	player.take_card(City::Istanbul);
	player.build(); //build in atlanta, but dont take card
	player.treat(City::Istanbul);
	CHECK(board[City::Istanbul] == true);
}

TEST_CASE("Dispatcher")
{
	Dispatcher player{board, City::HongKong};
	player.take_card(City::HongKong);
	player.build();
	CHECK_THROWS(player.treat(City::HongKong));
	player.fly_direct(City::NewYork);
}

TEST_CASE("Scientist")
{
	Scientist player{board, City::Madrid, 6};
	player.take_card(City::Madrid);
	player.build();
	player.take_card(City::Paris);
	player.take_card(City::London);
	player.take_card(City::NewYork);
	player.take_card(City::Montreal);
	player.take_card(City::Atlanta);
	player.take_card(City::Milan);

	CHECK_NOTHROW(player.discover_cure(Color::Blue));
}

TEST_CASE("Researcher")
{
	Researcher player{board, City::Moscow};
	player.take_card(City::Baghdad);
	player.take_card(City::Istanbul);
	player.take_card(City::Algiers);
	player.take_card(City::Cairo);
	player.take_card(City::Miami);
	player.take_card(City::Delhi);
	player.take_card(City::Kolkata);

	CHECK_NOTHROW(player.discover_cure(Color::Black));
}

TEST_CASE("Medic")
{
	board[City::Cairo] = 8;
	Medic player{board, City::Cairo};
	player.take_card(City::Cairo);
	player.build();
	CHECK(board[City::Cairo] == 8);
	player.drive(City::Algiers);
	player.take_card(City::Algiers);
	player.build();
	player.take_card(City::Moscow);
	player.take_card(City::Delhi);
	player.take_card(City::Tehran);
	player.take_card(City::Baghdad);
	player.take_card(City::Chennai);
	player.discover_cure(Color::Black);
	player.drive(City::Cairo);
	CHECK(board[City::Cairo] == 8);
}

TEST_CASE("Virologist")
{
	Virologist player{board, City::Istanbul};
	board[City::Madrid] = 6;
	player.take_card(City::Madrid);
	player.treat(City::Madrid);
	CHECK(board[City::Madrid] == 5);
}

TEST_CASE("GeneSplicer")
{
	GeneSplicer player{board, City::Sydney};
	CHECK_THROWS(player.build());
	player.take_card(City::Madrid);
	player.take_card(City::NewYork);
	player.take_card(City::Bogota);
	player.take_card(City::Istanbul);
	player.take_card(City::Jakarta);
	player.take_card(City::Sydney);
	player.build();
	player.treat(City::Sydney);
	CHECK(board[City::Sydney] == 6);
	player.discover_cure(Color::Red);
	player.treat(City::Sydney);
	CHECK(board[City::Sydney] == 0);
}

TEST_CASE("FieldDoctor")
{
	FieldDoctor player{board, City::Algiers};
	player.treat(City::Cairo);
	CHECK(board[City::Cairo] == 5);
}


TEST_CASE("everyCase")
{
	Virologist player{board, City::MexicoCity};
	CHECK_NOTHROW(player.drive(City::Miami));
	CHECK_NOTHROW(player.drive(City::Bogota));
	CHECK_THROWS(player.drive(City::SaoPaulo));
	CHECK_THROWS(player.fly_direct(City::SaoPaulo));
	CHECK_NOTHROW(player.take_card(City::SaoPaulo));
	CHECK_NOTHROW(player.fly_direct(City::SaoPaulo));
	CHECK_THROWS(player.fly_shuttle(City::Istanbul));
	CHECK_NOTHROW(player.fly_shuttle(City::Istanbul));
	CHECK_THROWS(player.fly_charter(City::Sydney));
	CHECK_NOTHROW(player.take_card(City::Algiers));
	CHECK_NOTHROW(player.fly_charter(City::MexicoCity));
	CHECK_THROWS(player.build());
	CHECK_NOTHROW(player.take_card(City::MexicoCity));
	CHECK_NOTHROW(player.build());
	CHECK_NOTHROW(player.take_card(City::MexicoCity));
	CHECK_THROWS(player.build());
	player.take_card(City::Madrid);
	player.take_card(City::London);
	player.take_card(City::Paris);
	CHECK_NOTHROW(player.discover_cure(Color::Black));
	CHECK_NOTHROW(player.drive(City::Washington));
	player.take_card(City::NewYork);
	player.take_card(City::Chicago);
	player.take_card(City::SanFrancisco);
	player.take_card(City::StPetersburg);
	player.take_card(City::Milan);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	board[City::Istanbul] = 9;
	CHECK_NOTHROW(player.treat(City::Istanbul));
	CHECK(board[City::Istanbul] == 8);
	CHECK_NOTHROW(player.treat(City::Istanbul));
	CHECK(board[City::Istanbul] == 0);
}