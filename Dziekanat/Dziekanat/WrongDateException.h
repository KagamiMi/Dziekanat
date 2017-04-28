#pragma once
class WrongDateException
{
public:
	bool wrongYear;
	bool wrongMonth;
	bool wrongDay;
	WrongDateException(bool wrongYear, bool wrongMonth, bool wrongDay);
	WrongDateException();
	~WrongDateException();
};

