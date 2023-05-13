#include "Board.h"
#include <iostream>
#include <sstream>
using namespace std;

// This file was written in Visual Studio 2022 by
// Kanat Ozgen

/// <summary>
/// Parametric Constructor for the Board class.
/// </summary>
/// <param name="Board Size"></param>
Board::Board(int num)
{
	first = new Node();
	Node* iterator = first;

	for (int i = 0; i < num - 1; i++)
	{
		iterator->next = new Node();
		iterator = iterator->next;
	}

	iterator->next = first;
}

/// <summary>
/// Destructor for the Board class. 
/// </summary>
Board::~Board()
{
	Node* iterator = first;

	while (iterator->next != first)
	{
		Node* buf = iterator;
		iterator = iterator->next;
		delete buf;
	}
}

/// <summary>
/// Who owns the block?
/// </summary>
/// <param name="Pointer to Node"></param>
/// <returns>Name of the Owner</returns>
string Board::who_owns(Node* block)
{
	return block->owner;
}

/// <summary>
/// Get the first element of the board.
/// </summary>
/// <returns>First block of the board</returns>
Node* Board::GetFirst()
{
	return first;
}

/// <summary>
/// Displays the board.
/// </summary>
void Board::display()
{
	Node* iterator = first;

	ostringstream output[3];

	if (iterator != NULL)
	{
		output[1] << "^  ";
		output[2] << "|";

		while (iterator->next != first)
		{				
			if (iterator->owner != "None")
			{
				output[0] << iterator->owner << " ->";
				output[1] << "      ";
				output[2] << "----<-";
			}

			else
			{
				output[0] << iterator->owner << "->";
				output[1] << "      ";
				output[2] << "----<-";
			}

			iterator = iterator->next;
		}

		output[0] << iterator->owner;
		output[1] << "|";
		output[2] << "--v";
	}

	for (int i = 0; i < 3; i++)
	{
		cout << output[i].str() << endl;
	}
}