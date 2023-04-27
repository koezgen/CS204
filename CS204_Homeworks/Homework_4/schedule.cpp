#include "schedule.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Written in Visual Studio 2022 by
// Kanat Ozgen

/// <summary>
/// This function returns the string that corresponds to
/// the enumerated variable.
/// </summary>
/// <param name="Integer between 0-6"></param>
/// <returns>Weekdays as string</returns>
string days_as_string(int day)
{
	if (day == Monday)
	{
		return "Monday";
	}

	if (day == Tuesday)
	{
		return "Tuesday";
	}

	if (day == Wednesday)
	{
		return "Wednesday";
	}

	if (day == Thursday)
	{
		return "Thursday";
	}

	if (day == Friday)
	{
		return "Friday";
	}

	if (day == Saturday)
	{
		return "Saturday";
	}

	if (day == Sunday)
	{
		return "Sunday";
	}

	// We will never get here, the variety of enum types is finite.
	return "00030973";
}

// Class Definitions
//****************************************************************************************************

/// <summary>
/// Default Constructor
/// </summary>
Schedule::Schedule()
{
	time_slots = 0;
	data = new string * [7];

	for (int i = 0; i < 7; i++)
	{
		data[i] = NULL;
	}
}

/// <summary>
/// Parametric Constructor
/// </summary>
/// <param name="Time slot count as integer"></param>
Schedule::Schedule(int c)
{
	time_slots = c;
	data = new string * [7];

	for (int i = 0; i < 7; i++)
	{
		data[i] = new string[c];
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < time_slots; j++)
		{
			data[i][j] = "free";
		}
	}
}

/// <summary>
/// Copy Constructor
/// </summary>
/// <param name="Schedule object"></param>
Schedule::Schedule(const Schedule& sch)
{
	time_slots = sch.time_slots;
	data = new string * [7];

	for (int i = 0; i < 7; i++)
	{
		data[i] = new string[sch.time_slots];

		for (int j = 0; j < sch.time_slots; j++)
		{
			data[i][j] = sch.data[i][j];
		}
	}
}

/// <summary>
/// Destructor
/// </summary>
Schedule::~Schedule()
{
	time_slots = 0;

	for (int i = 0; i < 7; i++)
	{
		delete[] data[i];
	}

	delete[] data;
}

/// <summary>
/// Accessor to time_slot
/// </summary>
/// <returns> Time Slot private data member</returns>
int Schedule::TimeSlotPart() const
{
	return time_slots;
}

/// <summary>
/// Accessor to data
/// </summary>
/// <returns>Data private data member</returns>
string** Schedule::DataPart() const
{
	return data;
}

/// <summary>
/// Mutator for time_slots
/// </summary>
/// <param name="Time Slot as integer"></param>
void Schedule::SetTimeSlot(int time)
{
	time_slots = time;
}

/// <summary>
/// Mutator to data. This member function takes string pointer
/// and manipulates the specific string pointer indexed by i
/// </summary>
/// <param name="String pointer"></param>
/// <param name="Index"></param>
void Schedule::SetData(string* dataline, unsigned short int i)
{
	data[i] = dataline;
}

/// <summary>
/// Mutator to data. This member function takes string and manipulates
/// the specific string indexed by i and j, in the string pointer pointer array.
/// </summary>
/// <param name="String"></param>
/// <param name="Index for 1st Dimension"></param>
/// <param name="Index for 2nd Dimension"></param>
void Schedule::SetData(string singledata, unsigned short int i, unsigned short int j)
{
	data[i][j] = singledata;
}

/// <summary>
/// Returns the respective index of the string pointer pointer.
/// </summary>
/// <param name=Day as enum></param>
/// <returns>String Array Pointer</returns>
string*& Schedule::operator[](Days rhs) const
{
	return data[rhs];
}

/// <summary>
/// Assign rhs to lhs schedule. This code took great inspiration from lab codes.
/// </summary>
/// <param name="Schedule as rhs"></param>
/// <returns> Assigned Schedule Object</returns>
const Schedule & Schedule::operator=(const Schedule &rhs)
{
	if (this != &rhs)
	{
		string** newData = new string * [7];

		for (int i = 0; i < 7; i++)
		{
			newData[i] = new string[rhs.TimeSlotPart()];
		}

		// Copy the data
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < rhs.TimeSlotPart(); j++)
			{
				newData[i][j] = rhs.DataPart()[i][j];
			}
		}

		// Deallocate the old memory
		for (int i = 0; i < 7; i++)
		{
			delete[] this->data[i];
		}
		delete[] this->data;

		// Update the data pointer
		this->data = newData;
		this->time_slots = rhs.TimeSlotPart();
	}

	return *this;
}

/// <summary>
/// Set a specific day to BUSY.
/// </summary>
/// <param name="Day as enum"></param>
/// <returns></returns>
Schedule Schedule::operator+(Days rhs)
{
	Schedule sch;
	sch.time_slots = time_slots;

	// I am creating a deep copy.
	for (int i = 0; i < 7; i++)
	{
		sch.data[i] = new string[TimeSlotPart()];

		for (int j = 0; j < TimeSlotPart(); j++)
		{
			sch.data[i][j] = data[i][j];
		}
	}

	for (int i = 0; i < TimeSlotPart(); i++)
	{
		sch.data[rhs][i] = "busy";
	}

	return sch;
}

/// <summary>
/// Set vertical to BUSY.
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Schedule Schedule::operator+(int rhs)
{
	Schedule sch;
	sch.time_slots = time_slots;

	// I am creating a deep copy.
	for (int i = 0; i < 7; i++)
	{	
		if (data[i] == NULL)
		{
			sch.data[i] = NULL;
		}

		else
		{
			sch.data[i] = new string[TimeSlotPart()];

			for (int j = 0; j < time_slots; j++)
			{
				sch.data[i][j] = data[i][j];
			}
		}
	}

	// It does not matter which one, just the first needs be checked.
	// Because other days should be null, by convention.
	if (sch.data[0] == NULL)
	{
		for (int i = 0; i < 7; i++)
		{
			if (sch.data[i] == NULL)
			{
				sch.data[i] = new string[rhs + 1];

				for (int j = 0; j < rhs; j++)
				{
					sch.data[i][j] = "    ";
				}

				sch.data[i][rhs] = "busy";
			}
		}

		sch.SetTimeSlot(rhs + 1);

		return sch;
	}
	
	// Case where the rhs is bigger or equal to time slots.
	// For example if time_slots is 3 and rhs is 3, it means that
	// Reallocation is necessary. Same for the case where time_slots is 2
	// and rhs is 3. Consider for all cases.
	else if (sch.time_slots <= rhs)
	{
		for (int i = 0; i < 7; i++)
		{
			// Create an arbitrary string array pointer
			// size of which should accomodate rhs^th column also.
			string* newData = new string[rhs + 1];

			// Everyone but the rhs'th object is directly copied.
			for (int j = 0; j < sch.time_slots; j++)
			{
				newData[j] = sch.data[i][j];
			}

			for (int k = sch.time_slots; k < rhs; k++)
			{
				newData[k] = "    ";
			}

			// Assignment of rhs'th column
			newData[rhs] = "busy";

			delete[] sch.data[i];
			sch.data[i] = newData;
		}

		sch.SetTimeSlot(rhs + 1);

		return sch;
	}

	// The trivial case where only a minuscule amount of manipulation is required.
	else
	{
		for (int i = 0; i < 7; i++)
		{
			sch.data[i][rhs] = "busy";
		}

		return sch;
	}
}
//**************************************************************************************

// FREE FUNCTIONS
//**************************************************************************************

/// <summary>
/// Print out the whole data structure.
/// </summary>
/// <param name="Ostream object"></param>
/// <param name="Schedule as const ref"></param>
/// <returns>Ostream object</returns>
ostream& operator<<(ostream& out, const Schedule& rhs)
{
	ostringstream output;

	for (int i = 0; i < 7; i++)
	{
		// String slicing. 
		string dayInit;
		dayInit = days_as_string(i);
		dayInit = dayInit.substr(0, 2) + ":";
		output << dayInit;

		// I need to check for nullity.
		if (rhs.DataPart()[i] != NULL)
		{
			for (int j = 0; j < rhs.TimeSlotPart(); j++)
			{
				output << " " << rhs.DataPart()[i][j];
			}
		}

		output << endl;
	}

	out << output.str();
	return out;
}

/// <summary>
/// Print out days corresponding to enum variables.
/// </summary>
/// <param name="Ostream object"></param>
/// <param name="Days as enum"></param>
/// <returns> Ostream object</returns>
ostream& operator<<(ostream& out, const Days& rhs)
{
	if (rhs == Monday)
	{
		out << "Monday";
	}

	else if (rhs == Tuesday)
	{
		out << "Tuesday";
	}

	else if (rhs == Wednesday)
	{
		out << "Wednesday";
	}

	else if (rhs == 3)
	{
		out << "Thursday";
	}

	else if (rhs == 4)
	{
		out << "Friday";
	}

	else if (rhs == 5)
	{
		out << "Saturday";
	}

	else if (rhs == 6)
	{
		out << "Sunday";
	}

	return out;
}

/// <summary>
/// Compare busyness in two schedules. Take the busy counts from both schedules and compare them. 
/// </summary>
/// <param name="Schedule 1"></param>
/// <param name="Schedule 2"></param>
/// <returns></returns>
bool operator<(const Schedule& lhs, const Schedule& rhs)
{
	int countBusyLhs = 0;
	int countBusyRhs = 0;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < lhs.TimeSlotPart(); j++)
		{
			if (lhs.DataPart()[i][j] == "busy")
			{
				countBusyLhs++;
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < rhs.TimeSlotPart(); j++)
		{
			if (rhs.DataPart()[i][j] == "busy")
			{
				countBusyRhs++;
			}
		}
	}

	return countBusyLhs < countBusyRhs;
}

/// <summary>
/// Returns the common free schedules.
/// </summary>
Schedule operator+(Schedule lhs, Schedule rhs)
{
	Schedule sch;
	sch.SetTimeSlot(lhs.TimeSlotPart());

	// I am creating a deep copy.
	for (int i = 0; i < 7; i++)
	{
		sch.SetData(new string[lhs.TimeSlotPart()], i);

		for (int j = 0; j < lhs.TimeSlotPart(); j++)
		{
			sch.SetData(lhs.DataPart()[i][j], i, j);
		}
	}

	// Compare everything, set busy to free if the corresponding timetable is busy in rhs.
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < sch.TimeSlotPart(); j++)
		{
			if ((sch.DataPart()[i][j] == "free") && (rhs.DataPart()[i][j] == "busy"))
			{
				sch.SetData("busy", i, j);
			}
		}
	}

	return sch;
}

/// <summary>
/// Returns the common busy schedules.
/// </summary>
Schedule operator*(Schedule lhs, Schedule rhs)
{
	Schedule sch;
	sch.SetTimeSlot(lhs.TimeSlotPart());

	// I am creating a deep copy.
	for (int i = 0; i < 7; i++)
	{
		sch.SetData(new string[lhs.TimeSlotPart()], i);

		for (int j = 0; j < lhs.TimeSlotPart(); j++)
		{
			sch.SetData(lhs.DataPart()[i][j], i, j);
		}
	}

	// Compare everything, set busy to free if the corresponding timetable is free in rhs.
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < sch.TimeSlotPart(); j++)
		{
			if ((sch.DataPart()[i][j] == "busy") && (rhs.DataPart()[i][j] == "free"))
			{
				sch.SetData("free", i, j);
			}
		}
	}

	return sch;
}
//******************************************************************************************