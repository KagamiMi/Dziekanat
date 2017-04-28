#include "WrongWeekException.h"

WrongWeekException::WrongWeekException(bool wrongLength, bool wrongWeekDay) : wrongLength(wrongLength), wrongWeekDay(wrongWeekDay)
{
}

WrongWeekException::WrongWeekException() : wrongLength(0), wrongWeekDay(0)
{
}


WrongWeekException::~WrongWeekException()
{
}
