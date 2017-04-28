#pragma once
#include "Week.h"
#include <conio.h>
#include <fstream>
class Schedule
{
	Date startingDate;
	Date endingDate;
protected:
	std::vector<Week> weeks;
public:
	virtual int information(std::ostream &s) = 0; //wypisuje informacje o planie i zwraca liczbe mowiaca jaki to plan
	Schedule(Date startingDate, Date endingDate);
	virtual ~Schedule();
	int selectMenu();
	std::vector<Week>::iterator weekMenu();
	void saveSchedule(std::vector<Week>::iterator week);
	std::vector<Week>::iterator getEndIterator();
	virtual Lesson getLesson() = 0;
	void addLesson(Date startWeek, int day, Lesson lesson);
	void deleteLesson(Date startWeek, int day, Lesson lesson);
	void addLesson(Date date, Lesson lesson);
	void saveDataFile(std::fstream &dataFile);
	int size();
};

