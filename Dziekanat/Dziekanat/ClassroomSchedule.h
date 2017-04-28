#pragma once
#include "Schedule.h"
#include <algorithm>
class ClassroomSchedule :
	public Schedule
{
	int classroom;
public:
	void writeWeek(Date start, Date end);
	ClassroomSchedule(Date startingDate, Date endingDate, int classroom);
	~ClassroomSchedule();
	int information(std::ostream &s);
	bool operator==(ClassroomSchedule classroom);
	static bool compare(ClassroomSchedule c1, ClassroomSchedule c2);
	Lesson getLesson();
};

