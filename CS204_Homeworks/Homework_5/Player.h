#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
using namespace std;

// This file was written in Visual Studio 2022 by
// Kanat Ozgen

class Player
{
	private:

		Board& board;
		string name;
		int balance;
		Node* pos;

	public:

		// Parametric Constructor
		Player(Board& gameboard, string name, int capital);

		// Mutators
		int move(int steps);
		void deposit_money(int add);
		void buy_slot(int slot);
		void pay_to_player(Player& otherPlayer, int money);
		
		// Accessors
		Node* where_am_I();
		int & get_balance();
		bool is_bankrupt();
		void display();
};

#endif