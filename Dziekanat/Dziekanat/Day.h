#pragma once
#include <ctime>
#include <list>
#include "Date.h"
#include "Lesson.h"
#include "AddingLessonException.h"
#include "SearchingLessonException.h"
#include <fstream>
#include <iostream>
#include <string>

class Day
{
	Date date; //data zajêæ
	std::list<Lesson> lessonsList; //lista z zajêciami w danym dniu
public:
	Day(Date date);
	~Day();
	void addLesson(Lesson lesson);
	std::list<Lesson>::iterator searchLesson(Lesson lesson);
	void deleteLesson(Lesson lesson);
	int getWeekDay();
	std::string getWeekDayName();
	void displayDay(std::ostream &s, int schedule);
	bool isEmpty();
	Date getDate();
	void saveDataFile(std::fstream &dataFile);
};
