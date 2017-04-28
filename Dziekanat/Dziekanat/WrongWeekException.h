#pragma once
class WrongWeekException
{
public:
	bool wrongLength;
	bool wrongWeekDay;
	WrongWeekException();
	WrongWeekException(bool wrongLength, bool wrongWeekDay);
	~WrongWeekException();
};

