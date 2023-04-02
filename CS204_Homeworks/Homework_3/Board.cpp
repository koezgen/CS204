#include "Board.h"
#include <iostream>
#include <string>
#include "CharStack.h"
using namespace std;

// Written in Visual Studio 2022 by
// Kanat Ozgen

Board::Board()
{
	// At first, nothing exists.
	head = NULL;
	tail = NULL;
	xCnt = 0;
	oCnt = 0;
}

void Board::createEmptySlotEnd()
{
	// There are three cases: 
	// 1. Board is Completely Empty,
	// 2. Board has only one slot stack,
	// 3. Board has multiple slots.

	// 1st case
	if ((head == NULL) && (tail == NULL))
	{
		head = new slot();
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}

	// 2nd case
	else if ((head == tail) && (head != NULL) && (tail != NULL))
	{
		tail = new slot();
		head->next = tail;
		tail->next = NULL;
		tail->prev = head;
	}

	// 3rd case
	else if (head != tail)
	{
		slot* append = new slot();
		tail->next = append;
		append->next = NULL;
		append->prev = tail;
		tail = append;
	}
}

void Board::createSlotEnd(char ch, int val)
{
	// There are three cases also: 
	// 1. Board is Completely Empty,
	// 2. Board has only one slot stack,
	// 3. Board has multiple slots.

	// 1st case
	if ((head == NULL) && (tail == NULL))
	{
		head = new slot();
		head->next = NULL;
		head->prev = NULL;

		for (int i = val; i > 0; i--)
		{
			head->slotStack.push(ch);

			if (ch == 'x')
			{
				xCnt++;
			}

			else
			{
				oCnt++;
			}
		}
		
		tail = head;
	}

	// 2nd case
	else if ((head == tail) && (head != NULL) && (tail != NULL))
	{
		tail = new slot();
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;

		for (int i = val; i > 0; i--)
		{
			tail->slotStack.push(ch);

			if (ch == 'x')
			{
				xCnt++;
			}

			else
			{
				oCnt++;
			}
		}
	}

	// 3rd case
	else if (head != tail)
	{
		slot* append = new slot();
		tail->next = append;
		append->next = NULL;
		append->prev = tail;
		tail = append;

		for (int i = val; i > 0; i--)
		{
			tail->slotStack.push(ch);

			if (ch == 'x')
			{
				xCnt++;
			}

			else
			{
				oCnt++;
			}
		}
	}
}

void Board::printBoard() const
{
	slot* loopvar = head;

	// This acts like a buffer between the string object and the data structure.
	slot* reverseStack = new slot();

	char bufchar = ' ';
	string lines[4];
	string lastline;

	while (loopvar != NULL)
	{
		if (loopvar->slotStack.isEmpty())
		{
			for (int i = 0; i < 4; i++)
			{
				lines[i] = lines[i] + ' ';
			}

			lastline = lastline + '^';
			loopvar = loopvar->next;
		}

		else
		{
			while (!(loopvar->slotStack.isEmpty()))
			{
				loopvar->slotStack.pop(bufchar);
				reverseStack->slotStack.push(bufchar);
			}

			for (int i = 0; i < 4; i++)
			{
				if (!(reverseStack->slotStack.isEmpty()))
				{
					reverseStack->slotStack.pop(bufchar);
					lines[i] = lines[i] + bufchar;
					loopvar->slotStack.push(bufchar);
				}

				else
				{
					lines[i] = lines[i] + ' ';
				}
			}

			lastline = lastline + "^";
			loopvar = loopvar->next;

		}
	}

	for (int i = 3; i >= 0; i--)
	{
		cout << lines[i] << endl;
	}

	cout << lastline << endl;

	// Discard the dynamically allocated data structures
	delete loopvar;
	delete reverseStack;
}

void Board::createSlotBegin(char ch, int val)
{
	slot* append = new slot();
	head->prev = append;
	append->next = head;
	append->prev = NULL;
	head = append;

	for (int i = val; i > 0; i--)
	{
		head->slotStack.push(ch);
		
		if (ch == 'x')
		{
			xCnt++;
		}

		else
		{
			oCnt++;
		}
	}
}

// Very straightforward
void Board::clearBoard()
{
	while (head != NULL)
	{
		slot* deleter = head;
		head = head->next;

		delete deleter;
	}
}

// Very straightforward
int Board::evaluateGame() const
{
	if (xCnt < oCnt)
	{
		return 1;
	}

	else if (xCnt > oCnt)
	{
		return 2;
	}

	else
	{
		return 3;
	}
}

void Board::movePiece(int val1, int val2)
{
	char piece = ' ';
	slot* choice = head;
	slot* target = head;

	for (int i = val1; i > 0; i--)
	{
		if (choice->next != NULL)
		choice = choice->next;
	}

	for (int i = val2; i > 0; i--)
	{
		if (target->next != NULL)
		target = target->next;
	}

	choice->slotStack.pop(piece);
	target->slotStack.push(piece);
}

void Board::destroySlot(int val)
{
	char discard = ' ';
	slot* index = head;

	for (int i = val; i > 0; i--)
	{	
		if (index->next != NULL)
		index = index->next;
	}

	while (index->slotStack.pop(discard))
	{
		if (discard == 'x')
		{
			xCnt--;
		}

		else
		{
			oCnt--;
		}
	}

	if ((index->next != NULL) && (index->prev != NULL))
	{
		index->prev->next = index->next;
		index->next->prev = index->prev;
		delete index;
	}

	else if ((index->prev != NULL) && (index->next == NULL))
	{
		index->prev->next = NULL;
		tail = index->prev;
		delete index;
	}

	else
	{
		// Cannot be NULL.
		index->next->prev = NULL;
		head = index->next;
		delete index;
	}
}

bool Board::targetSlotFull(int val) const
{
	slot* index = head;

	for (int i = val; i > 0; i--)
	{
		if (index->next != NULL)
		index = index->next;
	}

	return index->slotStack.isFull();
}

// There are two loops that check for both sides of the index.
bool Board::noMove(char ch, int val) const
{
	slot* loopvar = head;
	slot* index = loopvar;

	// Assume that there's no moves
	bool flag = true;
	char top = ' ';
	int count = 0;

	// Get the size of the structure
	while (loopvar != NULL)
	{
		if (loopvar->slotStack.pop(top))
		{
			loopvar->slotStack.push(top);

			if (top == ch)
			{
				count = 0;
				index = loopvar;
				top = ' ';

				while ((index->next != NULL) && (count < val))
				{
					index = index->next;
					count++;
				}

				if (index->slotStack.pop(top))
				{
					index->slotStack.push(top);

					if ((top == ch) && (count == val))
					{
						flag = false;
					}
				}

				else if (count == val)
				{
					flag = false;
				}

				count = 0;
				index = loopvar;
				top = ' ';

				while ((index->prev != NULL) && (count < val))
				{
					index = index->prev;
					count++;
				}

				if (index->slotStack.pop(top))
				{
					index->slotStack.push(top);

					if ((top == ch) && (count == val))
					{
						flag = false;
					}
				}

				else if (count == val)
				{
					flag = false;
				}

				loopvar = loopvar->next;
			}

			else
			{
				loopvar = loopvar->next;
			}
		}

		else
		{
			loopvar = loopvar->next;
		}
	}

	return flag;
}

// For all cases, there is a hierarchy for returns.
// That is 4, 1, 2, 3. Cases are investigated in this order.
int Board::validMove(char ch, int start, int step, int direction) const
{
	int size = 0;
	slot* index = head;
	char top = ' ';
	int dir = 0; 

	if (direction == 0)
	{
		dir = -1;
	}

	else
	{
		dir = 1;
	}

	// Means that there's at least one stack.
	if (index != NULL)
	{
		size++;
	}

	while (index != NULL)
	{
		index = index->next;
		size++;
	}

	size--;

	index = head;

	for (int i = start; i > 0; i--)
	{
		if (index->next != NULL)
			index = index->next;
	}

	if (index->slotStack.pop(top))
	{
		index->slotStack.push(top);

		if (top != ch)
		{
			return 4;
		}
	}

	else if (index->slotStack.isEmpty())
	{
		return 4;
	}

	index = head;

	if ((start < 0) || (start > size - 1))
	{
		return 1;
	}

	if (((start + step * dir) > size - 1) && (direction == 1))
	{
		return 2;
	}

	if (((start + step * dir) < 0) && (direction == 0))
	{
		return 2;
	}

	index = head;

	for (int i = start + step*dir; i > 0; i--)
	{
		if (index->next != NULL)
			index = index->next;
	}
	
	if (index->slotStack.pop(top))
	{	
		index->slotStack.push(top);

		if (top != ch)
		{
			return 3;
		}
	}

	if (!(index->slotStack.isFull()))
	{
		return 0;
	}

	// Will never enter here, for the sake of g++ compiler;
	return 0;
}