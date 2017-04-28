#pragma once
#include <ctime>
#include "Day.h"
#include "Date.h"
#include "WrongWeekException.h"
#include <vector> 
#include <algorithm>
#include <conio.h>
class Week
{
	std::vector <Day> weekDays; //wektor z dniami tygodnia 
	Date startingDate;
	Date endingDate;

public:
	std::vector<Day>::iterator getDay(int number);
	Week(Date startingDate, Date endingDate);
	~Week();
	void information(std::ostream &s);
	void displayWeek(std::ostream &s,int schedule);
	int daysMenu();
	Date getStart();
	Date getEnd();
	void saveDataFile(std::fstream &dataFile);
};

