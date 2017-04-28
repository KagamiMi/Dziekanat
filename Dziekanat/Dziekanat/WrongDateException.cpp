#include "WrongDateException.h"

WrongDateException::WrongDateException(bool wrongYear, bool wrongMonth, bool wrongDay) : wrongDay(wrongDay), wrongMonth(wrongMonth), wrongYear(wrongYear)
{
}

WrongDateException::WrongDateException() :wrongYear(0), wrongMonth(0), wrongDay(0)
{
}

WrongDateException::~WrongDateException()
{
}


