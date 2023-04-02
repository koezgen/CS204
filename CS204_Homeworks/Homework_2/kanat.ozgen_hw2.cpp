#include "feedback.h"
#include <iostream>
#include <string>
using namespace std;

// This file was written in Visual Studio 2022 by
// Kanat Ozgen

struct Node
{
	int digit = 0;
	Node *next;

	Node(int d, Node* p)
		: digit(d), next(p)
	{}
};

typedef Node* NodePtr;

// As the name implies, checks for duplicity in lists.
bool is_not_in_list(NodePtr head, int add)
{
	if (head == NULL)
	{
		return true;
	}

	else
	{
		NodePtr temp = head;

		while (temp->next != NULL)
		{
			if (temp->digit == add)
			{
				return false;
			}

			temp = temp->next;
		}

		if (temp->next == NULL)
		{
			if (temp->digit == add)
			{
				return false;
			}

			else
			{
				return true;
			}
		}
	}

	return true;
}

//I either directly used lecture codes, or took inspiration from:
//**************************************************************
void add_to_order(NodePtr& head, int add) 
{
	if (is_not_in_list(head, add))
	{
		NodePtr newNode = new Node(add, NULL);

		if (head == NULL || add < head->digit) 
		{
			newNode->next = head;
			head = newNode;
		}

		else
		{
			NodePtr prev = head;
			NodePtr curr = head->next;

			// This short circuits in case of NULL
			while (curr != NULL && curr->digit < add)
			{
				prev = curr;
				curr = curr->next;
			}

			if (curr == NULL || curr->digit > add)
			{
				prev->next = newNode;
				newNode->next = curr;
			}

			else
			{
				delete newNode;
			}
		}
	}
}

void remove_from_order(NodePtr& head, int add) 
{
	// No need to put all the function inside the is_not_in_list bool block
	// Since it is arbitrary to know it for the case of removal.
	// If exists, remove; if doesn't, do nothing.

	if ((head != NULL) && (head->digit == add))
	{
		NodePtr temp = head;
		head = head->next;
		delete temp;
	}

	else if (head != NULL)
	{
		NodePtr prev = head;
		NodePtr current = head->next;

		// Short Circuit
		while (current != NULL && current->digit != add)
		{
			prev = current;
			current = current->next;
		}

		if (current != NULL)
		{
			prev->next = current->next;
			delete current;
		}
	}
}

void DeleteList(NodePtr head)
{
	if (head != NULL)
	{
		DeleteList(head->next);
		delete head;
	}
}
//**************************************************************

// This parses the feedback string and iterates for every case.
// In this function, instead of loops, i decided to use modulus operation.
// There were problems but for this kind of loop-like iteration, it was good.
void oracle_feedback(int loopvar, char digit, char feedback, NodePtr Possible[], NodePtr Impossible[]) 
{
	if (feedback == 'G')
	{
		add_to_order(Possible[loopvar], int(digit) - 48);

		for (int i = 1; i < 10; i++)
		{
			add_to_order(Impossible[loopvar], ((int(digit) - 48) + i) % 9);
		}

		// This accounts for modulus operation's faults.
		add_to_order(Impossible[loopvar], 9);

		remove_from_order(Possible[(loopvar + 1) % 3], int(digit) - 48);
		remove_from_order(Possible[(loopvar + 2) % 3], int(digit) - 48);
		remove_from_order(Impossible[loopvar], int(digit) - 48);

		add_to_order(Impossible[(loopvar + 1) % 3], int(digit) - 48);
		add_to_order(Impossible[(loopvar + 2) % 3], int(digit) - 48);
	}

	else if (feedback == 'Y')
	{
		add_to_order(Impossible[loopvar], int(digit) - 48);
		
		remove_from_order(Possible[loopvar], int(digit) - 48);

		if (is_not_in_list(Impossible[(loopvar + 1) % 3 ], int(digit) - 48))
		{
			add_to_order(Possible[(loopvar + 1) % 3], int(digit) - 48);
		}

		if (is_not_in_list(Impossible[(loopvar + 2) % 3], int(digit) - 48))
		{
			add_to_order(Possible[(loopvar + 2) % 3], int(digit) - 48);
		}
	}

	else if (feedback == 'R')
	{
		add_to_order(Impossible[loopvar], int(digit) - 48);
		add_to_order(Impossible[(loopvar + 1) % 3], int(digit) - 48);
		add_to_order(Impossible[(loopvar + 2) % 3], int(digit) - 48);
	}
}

// Recursive function that prints the linked list.
void printList(NodePtr begin)
{
	if (begin == NULL)
	{
		cout << "";
	}

	else
	{
		cout << begin->digit << " ";

		if (begin->next != NULL)
		{
			printList(begin->next);
		}
	}
}

// This is to check if the game ended or not. 
int HoldCounts(NodePtr head)
{
	int count = 1;
	NodePtr loopvar = head;

	if (loopvar == NULL)
	{
		return 0;
	}

	while (loopvar->next != NULL)
	{
		count++;
		loopvar = loopvar->next;
	}

	return count;
}

// This checks the integrity of the input.
bool input_checker(string number)
{
	if (number.length() != 3)
	{
		return false;
	}

	else
	{
		for (int i = 0; i < number.length(); i++)
		{
			if ((int(number.at(i)) - 48 > 9) || (int(number.at(i)) - 48 < 0))
			{
				return false;
			}
		}
	}

	return true;
}

// This checks the unicity of the elements of the string.
bool is_unique(string number)
{
	bool flag = true;

	for (int i = 0; i < number.length(); i++)
	{
		for (int j = 0; j < number.length(); j++)
		{
			if ((number[i] == number[j]) && (i != j))
			{
				flag = false;
			}
		}
	}

	return flag;
}

// This checks the lengths of linked lists.
bool is_game_finished(NodePtr Possibles[], NodePtr Impossibles[])
{
	bool flag = false;

	if ((HoldCounts(Impossibles[0]) == 9) && (HoldCounts(Impossibles[1]) == 9) && (HoldCounts(Impossibles[2]) == 9))
	{
		flag = true;
	}

	return flag;
}

// This prints out the overall structure with some terminal printouts.
void printLinkedLists(NodePtr Possibles[], NodePtr Impossibles[])
{
	cout << "Linked lists:" << endl;
	cout << "Slot: 1" << endl;
	cout << "Impossibles: ";
	printList(Impossibles[0]);
	cout << endl << "Possibles: ";
	printList(Possibles[0]);
	cout << endl << endl;

	cout << "Slot: 2" << endl;
	cout << "Impossibles: ";
	printList(Impossibles[1]);
	cout << endl << "Possibles: ";
	printList(Possibles[1]);
	cout << endl << endl;

	cout << "Slot: 3" << endl;
	cout << "Impossibles: ";
	printList(Impossibles[2]);
	cout << endl << "Possibles: ";
	printList(Possibles[2]);
	cout << endl << endl;
}

// Everything happens inside the do-while block. 
int main()
{
	int game_ID = 0;
	string guess;

	// These are the arrays that hold the Node pointers.
	NodePtr Possibles[3] = { NULL, NULL, NULL };
	NodePtr Impossibles[3] = { NULL, NULL, NULL };

	cout << "Please enter a game ID." << endl;
	cin >> game_ID;

	// Parse the input here, to the linked lists. Also take the feedback from the oracle here.
	do
	{
		cout << "Enter your guess." << endl;
		cin >> guess;

		while ((!input_checker(guess)) || (!is_unique(guess)))
		{
			cout << "Invalid guess. Enter your guess." << endl;
			cin >> guess;
		}

		string oracle_response;
		oracle_response = get_the_feedback(guess, game_ID);

		for (int i = 0; i < guess.length(); i++)
		{
			oracle_feedback(i, guess[i], oracle_response[i], Possibles, Impossibles);
		}

		printLinkedLists(Possibles, Impossibles);

		if (is_game_finished(Possibles, Impossibles))
		{
			for (int i = 0; i < 3; i++)
			{
				if (Possibles[i] == NULL)
				{
					for (int j = 0; j < 10; j++)
					{
						if (is_not_in_list(Impossibles[i], j))
						{
							Possibles[i] = new Node(j, NULL);
						}
					}
				}
			}
		}

	} while (!is_game_finished(Possibles, Impossibles));


	// They can never be NULL.
	cout << "The secret number is: " << Possibles[0]->digit << Possibles[1]->digit << Possibles[2]->digit << endl;
	cout << "Congrats! Now, deleting the lists..." << endl;

	for (int i = 0; i < 3; i++)
	{
		DeleteList(Impossibles[i]);
		DeleteList(Possibles[i]);
	}

	// Since lists are statically allocated, no further action can be taken.
	for (int i = 0; i < 3; i++)
	{
		Possibles[i] = NULL;
		Impossibles[i] = NULL;
	}  

	_CrtDumpMemoryLeaks();

	return 0;
}