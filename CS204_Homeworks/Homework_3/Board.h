#ifndef BOARD_H
#define BOARD_H

#include "CharStack.h"

struct slot
{
	slot* next;
	slot* prev;
	CharStack slotStack;
	slot()
	{}
};

class Board
{
	private:
		slot* head;
		slot* tail;
		int xCnt;
		int oCnt;

	public:
		// Constructor
		Board();

		// Accessors
		void printBoard() const;
		bool noMove(char ch, int val) const;
		int validMove(char ch, int val1, int val2, int val3) const;
		bool targetSlotFull(int val) const;
		int evaluateGame() const;

		// Mutators
		void createEmptySlotEnd();
		void createSlotEnd(char ch, int val);
		void createSlotBegin(char ch, int val);
		void movePiece(int val1, int val2);
		void destroySlot(int val);
		void clearBoard();
};

#endif