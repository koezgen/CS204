#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
using namespace std;

class Player
{
	private:
		Board& board;
		string name;
		int balance;
		Node* pos;
	public:
		Player(Board& gameboard, string name, int capital);
		int move(int steps);
		Node* where_am_I();
		void pay_to_player(Player& otherPlayer, int money);
		int & get_balance();
		void deposit_money(int add);
		void buy_slot(int slot);
		bool is_bankrupt();
		void display();
};

#endif