#include "AddingLessonException.h"

AddingLessonException::AddingLessonException(bool wrongStartHour, bool wrongEndHour) : wrongStartHour(wrongStartHour), wrongEndHour(wrongEndHour)
{
}

AddingLessonException::AddingLessonException() : wrongStartHour(0), wrongEndHour(0)
{
}


AddingLessonException::~AddingLessonException()
{
}
