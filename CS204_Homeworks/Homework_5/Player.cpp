#include "Player.h"
#include <iostream>
#include <sstream>
using namespace std;

// This file was written in Visual Studio 2022 by
// Kanat Ozgen

/// <summary>
/// Player object.
/// </summary>
/// <param name="gameboard">Game Board</param>
/// <param name="pname">Player Name</param>
/// <param name="capital">Capital</param>
/// <param name="position">Position</param>
Player::Player(Board& gameboard, string pname, int capital)
	:board(gameboard)
{
	pos = board.GetFirst();
	name = pname;
	balance = capital;
}

/// <summary>
/// Where the 
/// </summary>
/// <returns>Reference to balance. This is because I want to manipulate another one's capital in some places.</returns>
int & Player::get_balance()
{
	return balance;
}

/// <summary>
/// Where the player is
/// </summary>
/// <returns>Position</returns>
Node* Player::where_am_I()
{
	return pos;
}

/// <summary>
/// Moves for a certain amount.
/// </summary>
/// <param name="steps"></param>
/// <returns>Returns 1 if passed from first block of the board, 0 otherwise.</returns>
int Player::move(int steps)
{
	Node* iterator = pos;
	int token = 0;

	for (int i = 0; i < steps; i++)
	{
		if (iterator->next == board.GetFirst())
		{
			token = 1;
		}

		iterator = iterator->next;
	}

	pos = iterator;
	return token;
}

/// <summary>
/// Transaction between players.
/// </summary>
/// <param name="otherPlayer"></param>
/// <param name="transaction"></param>
void Player::pay_to_player(Player& otherPlayer, int transaction)
{
	otherPlayer.get_balance() += transaction;
	balance -= transaction;
}

/// <summary>
/// Add the parameter to the player's balance
/// </summary>
/// <param name="add"></param>
void Player::deposit_money(int add)
{
	balance += add;
}

/// <summary>
/// Change the owner of the node, 
/// </summary>
/// <param name="slot"></param>
void Player::buy_slot(int slot)
{
	balance -= slot;
	pos->owner = this->name;
}

/// <summary>
/// Is the player bankrupt?
/// </summary>
/// <returns>If the balance is smaller than 0, return true; else return false. </returns>
bool Player::is_bankrupt()
{
	if (balance < 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

/// <summary>
/// Display the player info.
/// </summary>
void Player::display()
{
	// I will take the ostringstream approach here.
	ostringstream playerinfo;
	
	Node* iterator = board.GetFirst();

	while (iterator != pos)
	{
		playerinfo << "      ";
		iterator = iterator->next;
	}

	playerinfo << name << " " << balance;
	cout << playerinfo.str() << endl;
}