#include <thread>
#include <mutex>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include "IntQueueHW6.h"
using namespace std;

// This file was written in Visual Studio 2022 by
// Kanat Ozgen

mutex QUEUE_MUTEX;

/// <summary>
/// Player function. This function gets called multiple times and each
/// instance runs in parallel.
/// </summary>
/// <param name="player_ID">Player Number</param>
/// <param name="array">Queue</param>
/// <param name="time">Time of main</param>
void player(int player_ID, IntQueueHW6 * queue, struct tm* time)
{
	// Thread sleeps until the run signal is recieved.
	this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(time)));

	// Lock other threads.
	QUEUE_MUTEX.lock();
	if (!queue->isFull())
	{
		cout << "Player " << player_ID << " captured a chair at " << put_time(time, "%X") << "." << endl;
		queue->enqueue(player_ID);
		QUEUE_MUTEX.unlock();
	}

	else
	{
		cout << "Player " << player_ID << " couldn't capture a chair." << endl;
		QUEUE_MUTEX.unlock();
	}
}

int main()
{
	// The first section of the program. Get the input.
	int player_count = 0;
	int thread_array = 0;
	int dummy = 0;

	cout << "Welcome to Musical Chairs game!";
	cout << endl;
	cout << "Enter the number of players in the game:";
	cout << endl;
	cin >> player_count;
	cout << "Game Start!";
	cout << endl << endl;
	
	// Save thread array count to a constant
	thread_array = player_count;

	/// Get system time
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm* ptm = new struct tm;
	localtime_s(ptm, &tt);
	cout << "Time is now " << put_time(ptm, "%X") << endl;
	ptm->tm_sec += 2;

	//Integer array
	IntQueueHW6* gamequeue = new IntQueueHW6(player_count - 1);
	IntQueueHW6 buffer(player_count - 1);

	//Dynamically allocated thread array pointer.
	thread* players = new thread[player_count];

	//Initialize threads.
	for (int i = 0; i < player_count; i++)
	{
		players[i] = thread(&player, i, gamequeue, ptm);
	}

	/// Join all player threads.
	for (int i = 0; i < player_count; i++)
	{
		players[i].join();
	}

	cout << "Remaining players are as follows:";

	// Empty the queue to buffer
	while (!gamequeue->isEmpty())
	{
		gamequeue->dequeue(dummy);
		cout << " " << dummy;
		buffer.enqueue(dummy);
	}

	// Decrement the player count and delete the dynamically allocated queue.
	cout << endl << endl;
	player_count--;
	delete gamequeue;

	// The first game is special.
	// A separate loop is needed for the rest of the game.
	while (player_count != 1)
	{
		cout << "Time is now " << put_time(ptm, "%X") << endl;
		ptm->tm_sec += 2;

		// Reallocate the integer queue. It has one less slot. 
		IntQueueHW6* gamequeue = new IntQueueHW6(player_count - 1);

		while (!buffer.isEmpty())
		{
			buffer.dequeue(dummy);
			players[dummy] = thread(&player, dummy, ref(gamequeue), ptm);
		}

		// For all the threads available, I check for joinability.
		// Because there is a chance that the player might have lost in other games.
		// I have no way of knowing which player stands, so I check for all the threads
		// That were initialized before.
		for (int i = 0; i < thread_array; i++)
		{
			if (players[i].joinable())
			{
				players[i].join();
			}
		}

		cout << "Remaining players are as follows:";

		// Same procedure as above.
		while (!gamequeue->isEmpty())
		{
			gamequeue->dequeue(dummy);
			cout << " " << dummy;
			buffer.enqueue(dummy);
		}

		// Same procedure as above
		cout << endl << endl;
		player_count--;
		delete gamequeue;
	}

	// Game ended. Delete the dynamically allocated array and print the ID of the winner.
	buffer.dequeue(dummy);
	delete[] players;
	cout << "Game over!" << endl;
	cout << "Winner is Player " << dummy << "!";

	return 0;
}