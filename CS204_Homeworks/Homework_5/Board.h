#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;

// This file was written in Visual Studio 2022 by
// Kanat Ozgen

// Primary data structure that makes up the board.
struct Node
{
	string owner;
	Node* next;

	// Default Constructor
	Node()
		:owner("None"), next(NULL) {};

	// Parametric Constructor
	Node(string o, Node* p)
		:owner(o), next(p) {};
};

class Board
{
	private:

		Node* first;

	public:

		// Parametric Constructor
		Board(int num);
		// Destructor
		~Board();

		// Accessors
		void display();
		string who_owns(Node* block);
		Node* GetFirst();
};

#endif