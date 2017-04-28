#pragma once
#include "Schedule.h"
#include <string>
class TeacherSchedule :
	public Schedule
{
	std::string teacherName;
	std::string teacherSurname;
public:
	TeacherSchedule(Date startingDate, Date endingDate, std::string teacherName, std::string teacherSurname);
	~TeacherSchedule();
	void writeWeek(Date start, Date end);
	int information(std::ostream &s);
	bool operator==(TeacherSchedule teacher);
	static bool compare(TeacherSchedule t1, TeacherSchedule t2);
	Lesson getLesson();
};

