#include "Time.h"
#include <cmath>
#include <iostream>


Time::Time() : hour(0), minutes(0)
{
}

Time::Time(int _hour, int _minutes) 
{//wyjatek na z³y zakres
	bool wrongHour = 0, wrongMinutes = 0;
	
	if ((_hour > 23) || (_hour < 0)) //sprawdzenie zakresu godzin
	{
		wrongHour = 1;
	}

	if ((_minutes > 59) || (_minutes < 0)) //sprawdzenie zakesu minut
	{
		wrongMinutes = 1;
	}

	if (wrongHour || wrongMinutes) //sprawdzenie czy trzeba rzucic wyjatek
	{
		throw WrongTimeException(wrongHour,wrongMinutes);
	}

	hour = _hour;
	minutes = _minutes;
}

Time::~Time()
{
}

Time Time::differenceModule(Time t1, Time t2) { //zwraca ró¿nicê pomiêdzy dwoma godzinami
	int all_minutes_t1, all_minutes_t2;
	all_minutes_t1 = 60 * t1.hour + t1.minutes; //zmieniamy na same minuty
	all_minutes_t2 = 60 * t2.hour + t2.minutes;

	int all_minutes_temp, hour_temp = 0, minutes_temp;
	
	all_minutes_temp = abs(all_minutes_t1-all_minutes_t2); //obliczamy ró¿nicê
	while (all_minutes_temp >= 60) { //wracamy do godzin i minut
		hour_temp++;
		all_minutes_temp -= 60;
	}
	minutes_temp = all_minutes_temp;
	return Time(hour_temp,minutes_temp); //zwa=racamy ró¿nicê
}


bool Time::operator>=(Time t) {
	if (hour > t.hour) {
		return true; //gdy godzina wieksza to na pewno wieksze
	}
	else if (hour == t.hour) { //jesli rowne
		if (minutes >= t.minutes) { //to sprawdzamy minuty
			return true;
		}
	}
	return false; //gdy nie
}

bool Time::operator<=(Time t) {
	if (hour < t.hour) {
		return true;
	}
	else if (hour == t.hour) {
		if (minutes <= t.minutes) {
			return true;
		}
	}
	return false;
}

bool Time::operator==(Time t) {
	return ((hour == t.hour) && (minutes == t.minutes));
}

std::ostream & operator<<(std::ostream &s, const Time &t) {
	if (t.hour < 10) {
		s << 0 << t.hour << ":";
	}
	else {
		s << t.hour << ":";
	}

	if (t.minutes < 10) {
		s << 0 << t.minutes;
	}
	else {
		s << t.minutes;
	}

	return s;
}

std::istream &operator>>(std::istream &s, Time &t) {
	s >> t.hour;
	s.ignore();
	s >> t.minutes;

	return s;
}