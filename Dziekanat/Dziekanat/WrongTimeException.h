#pragma once
class WrongTimeException
{
public:
	bool wrongHour;
	bool wrongMinutes;
	WrongTimeException(bool wrongHour, bool wrongMinutes);
	WrongTimeException();
	~WrongTimeException();
};

