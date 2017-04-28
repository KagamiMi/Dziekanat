#include "WrongTimeException.h"

WrongTimeException::WrongTimeException(bool wrongHour, bool wrongMinutes) : wrongHour(wrongHour), wrongMinutes(wrongMinutes)
{
}

WrongTimeException::WrongTimeException() : wrongHour(0), wrongMinutes(0)
{
}


WrongTimeException::~WrongTimeException()
{
}
