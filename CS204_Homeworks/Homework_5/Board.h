#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;

struct Node
{
	string owner;
	Node* next;
	Node()
		:owner("None"), next(NULL) {};
	Node(string o, Node* p)
		:owner(o), next(p) {};
};

class Board
{
	private:
		Node* first;
	public:
		Board(int num);
		~Board();
		void display();
		string who_owns(Node* block);
		Node* GetFirst();
};

#endif