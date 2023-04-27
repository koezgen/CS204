#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>
using namespace std;

enum Days { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

class Schedule
{
private:
	int time_slots;
	string** data;

public:
	// Constructors, accessors.
	Schedule();
	Schedule(const Schedule& sch);
	Schedule(int c);
	~Schedule();
	int TimeSlotPart() const;
	void SetTimeSlot(int time);
	string** DataPart() const;

	// Mutators of the class.
	void SetData(string* dataline, unsigned short int i);
	void SetData(string singledata, unsigned short int i, unsigned short int j);

	// There are 4 member functions defined.
	const Schedule& operator=(const Schedule& rhs);
	Schedule operator+(Days rhs);
	Schedule operator+(int rhs);
	string*& operator [] (Days rhs) const;
};

// There will be 5 free operator overloading functions.
Schedule operator+(Schedule lhs, Schedule rhs);
Schedule operator*(Schedule lhs, Schedule rhs);
bool operator < (const Schedule & lhs, const Schedule & rhs);
ostream& operator<<(ostream& out, const Schedule& rhs);
ostream& operator<<(ostream& out, const Days& rhs);

#endif