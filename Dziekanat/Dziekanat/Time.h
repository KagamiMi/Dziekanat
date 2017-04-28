#pragma once
#include "WrongTimeException.h"
#include <iostream>
class Time
{
	int hour;
	int minutes;
public:
	Time();
	Time(int hour, int minutes);
	~Time();
	static Time differenceModule(Time t1, Time t2);
	bool operator>=(Time t); 
	bool operator<=(Time t); 
	bool operator==(Time t);
	friend std::ostream & operator<<(std::ostream &s, const Time &t);
	friend std::istream &operator>>(std::istream &s, Time &t);
};

