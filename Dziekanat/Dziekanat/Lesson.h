#pragma once
#include <string>
#include "Time.h"
#include "Date.h"
#include "WrongLessonException.h"
#include <iostream>


class Lesson
{
	std::string name; //nazwa zajec
	std::string type; //typ zajec
	Time start; //czas rozpoczecia zajec
	Time end; //czas zakonczenia zajec 
	
	int classroom;
	std::string teacherName;
	std::string teacherSurname;
	int groupNumber;
	int groupSemester;
	std::string groupSpecialization;
public:
	Lesson(std::string name, std::string type, Time start, Time end, int classroom, std::string teacherName, std::string teacherSurname,
		int groupNumber, int groupSemester, std::string groupSpecialization);
	~Lesson();
	Time startTime();
	Time endTime();
	bool operator==(Lesson lesson);
	friend std::ostream & operator<<(std::ostream &s, const Lesson &l);
	void write(std::ostream &s,int schedule);
	int getClassroom();
	std::string getTeacherName();
	std::string getTeacherSurname();
	int getGroupNumber();
	int getGroupSemester();
	std::string getGroupSpecialization();
};

