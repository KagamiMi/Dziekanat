#pragma once
class AddingLessonException
{
public:
	bool wrongStartHour;
	bool wrongEndHour;
	AddingLessonException(bool wrongStartHour, bool wrongEndHour);
	AddingLessonException();
	~AddingLessonException();
};

