#pragma once
#include "Schedule.h"
class GroupSchedule :
	public Schedule
{
	int groupNumber;
	int groupSemester;
	std::string groupSpecialization; 
public:
	GroupSchedule(Date startingDate, Date endingDate, int groupNumber, int groupSemester, std::string groupSpecialization);
	~GroupSchedule();
	void writeWeek(Date start, Date end);
	int information(std::ostream &s);
	bool operator==(GroupSchedule group);
	static bool compare(GroupSchedule g1, GroupSchedule g2);
	Lesson getLesson();
};

