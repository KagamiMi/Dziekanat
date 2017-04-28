#include "Date.h"
#include <string>

const std::string Date::daysOfWeek[7] = {"Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota", "Niedziela"};
const int Date::daysOfYear[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

Date::Date() {

}

Date::Date(int _day, int _month, int _year) 
{	
	bool wrongYear = 0, wrongMonth = 0, wrongDay = 0;
	//sprawdzenie czy dobrze podana data - inaczej wyj¹tek
	if (_year <= 0) { //sprawdzenie roku
		wrongYear = 1;
	}
	if ((_month > 12) || (_month < 1)) { //sprawdzenie miesiaca
		wrongMonth = 1;
	}
	if (_day < 1) { //zaczynamy sprawdzanie dnia
		wrongDay = 1;
	}
	else if (_month != 12) { //gdy nie jest to ostatni miesi¹c
		if (_month == 2) { //gdy drugi miesiac, to musimy sprawdzic czy rok przestepny
			if (isLeapYear(_year)) {
				if (_day > (daysOfYear[_month] - daysOfYear[_month - 1] + 1)) { //dodajemy jeden i sprawdzamy z liczba dni miesiaca
					wrongDay = 1;
				}
			}
			else {
				if (_day > (daysOfYear[_month] - daysOfYear[_month - 1])) { //sprawdzamy z liczba dni miesiaca
					wrongDay = 1;
				}
			}
		}
		else {
			if (_day > (daysOfYear[_month] - daysOfYear[_month - 1])) { //sprawdzamy z liczba dni miesiaca
				wrongDay = 1;
			}
		}
	}
	else { //gdy dwunasty miesiac
		if (_day > (365 - daysOfYear[_month - 1])) {
			wrongDay = 1;
		}
	}

	if (wrongYear || wrongMonth || wrongDay) {
		throw WrongDateException(wrongYear,wrongMonth,wrongDay);
	}
	

	//jeœli wszystko ok, to mo¿emy inicjalizowaæ
	day = _day;
	month = _month;
	year = _year;

	int temp1, temp2, firstDayOfYear, dayOfYear;
	//obliczenie dnia tygodnia dla 1 stycznia danego roku
	temp1 = (year - 1) % 100;
	temp2 = ((year - 1) - temp1) / 100;
	firstDayOfYear = ((temp2 % 4) * 5 + temp1 + (temp1 / 4)) % 7; 
	dayOfYear = daysOfYear[month - 1] + day;
	if (isLeapYear(year)) { //gdy rok przestêpny
		if (month > 2) { //gdy po lutym
			dayOfYear++;
		}
	}
	yearDay = dayOfYear;
	weekDay = (firstDayOfYear + dayOfYear - 1) % 7;
}


Date::~Date()
{
}


bool Date::operator==(Date date) {
	if ((day == date.day) && (month == date.month) && (year == date.year)) {
		return true; //jeœli wszystkie dni te same, zwracamy true
	}
	return false; //jeœli czymœ siê ró¿ni¹, zwracamy false
}

void Date::nextWeekDay() { //zmiana na nastepny dzien tygodnia
	if (weekDay != 6) {
		weekDay++;
	}
	else {
		weekDay = 0;
	}
}

void Date::previousWeekDay() {
	if (weekDay != 0) {
		weekDay--;
	}
	else {
		weekDay = 6;
	}
}

Date Date::operator++(int) {
	Date temp = *this;
	if (month != 12) { //gdy to nie jest ostatni miesiac
		if (isLeapYear(year) && (month == 2)) { //gdy luty w roku przestêpnym
			if (day == 29) { //przechodzimy do nastepnego miesi¹ca gdy ostatni dzieñ
				day = 1;
				month++;
				yearDay++;
			}
			else { //gdy dzieñ w trakcie miesi¹ca
				day++;
				yearDay++;
			}
		}
		else {
			if (isLeapYear(year) && (month > 2)) {
				if ((daysOfYear[month]+1) == yearDay) { //gdy natrafiliœmy na ostatni dzieñ w miesi¹cu
					day = 1;
					month++;
					yearDay++;
				}
				else { //gdy dzieñ w trakcie miesi¹ca
					day++;
					yearDay++;
				}
			}
			else {
				if (daysOfYear[month] == yearDay) { //gdy natrafiliœmy na ostatni dzieñ w miesi¹cu
					day = 1;
					month++;
					yearDay++;
				}
				else { //gdy dzieñ w trakcie miesi¹ca
					day++;
					yearDay++;
				}
			}

		}
	}
	else { //gdy ostatni miesiac
		if (isLeapYear(year)) { //gdy rok przestêpny
			if (yearDay == 366) { //gdy ostatni dzieñ w roku
				day = 1;
				month = 1;
				year++;
				yearDay = 1;
			}
			else {
				day++; // gdy dzieñ w trakcie miesi¹ca
				yearDay++;
			}
		}
		else { //gdy rok normalny
			if (yearDay == 365) { //gdy ostatni dzieñ w roku
				day = 1;
				month = 1;
				yearDay = 1;
				year++;
			}
			else {
				day++; // gdy dzieñ w trakcie miesi¹ca
				yearDay++;
			}
		}
	}
	nextWeekDay();
	return temp;
}

bool Date::isLeapYear(int _year) {
	if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0)) {
		return true; //jest przestepny
	} 
	return false; //zwykly rok
}

std::ostream &operator<<(std::ostream &s, const Date &d) {
	if (d.day < 10) {
		s << 0 << d.day << ".";
	}
	else {
		s << d.day << ".";
	}

	if (d.month < 10) {
		s << 0 << d.month << ".";
	}
	else {
		s << d.month << ".";
	}

	s << d.year;

	return s;
}

bool Date::operator<=(Date date) {
	if (year < date.year) {
		return true;
	}
	else if (year == date.year) {
		if (month < date.month) {
			return true;
		}
		else if (month == date.month) {
			if (day <= date.day) {
				return true;
			}
		}
	}
	return false;
}

int Date::getWeekDay() {
	return weekDay;
}

int Date::operator-(Date date) {
	if (year == date.year) { //gdy rowne roki, to zwracamy roznice pomiedzy dniami po prostu
		return yearDay - date.yearDay;
	}
	int difference = 0;
	Date temp1(*this), temp2(date);
	if (*this <= date) {
		temp1 = date;
		temp2 = *this;
	}
	//temp1 - wieksza data, temp2 - mniejsza data
		difference += temp1.yearDay; //dodajemy dni z wiekszego roku
		if (isLeapYear(temp2.year)) { //gdy mniejszy rok przestepny
			difference += (366 - temp2.yearDay);
		}
		else{
			difference += (365 - temp2.yearDay); //gdy zwykly
		}
		for (int i = (temp2.yearDay + 1); i < temp1.yearDay; i++) { //dla reszty lat pomiêdzy
			if (isLeapYear(i)) {
				difference += 366;
			}
			else {
				difference += 365;
			}
		}
		if (!(*this <= date)) {
			return difference; //gdy pierwszy byl wiekszy
		}
		else {
			return -difference; //gdy drugi byl wiekszy, bedzie ujemna liczba
		}

}

Date Date::operator+(int number) {
	Date temp(*this); //kopia obecnej daty na ktorej bedziemy pracowac
	int temp_days = day + number; //poczatkowo dodajemy dni
	int temp_change; //zmiana ktora bedziemy wprowadzac
	if (month != 12) { //gdy to nie jest ostatni miesiac
	if (month == 2) { //gdy drugi miesiac, to musimy sprawdzic czy rok przestepny
		if (isLeapYear(year)) {
			if (temp_days > (daysOfYear[month] - daysOfYear[month - 1] + 1)) { //dodajemy jeden i sprawdzamy z liczba dni miesiaca
				//gdy wychodzimy poza miesiac
				//rekurencyjnie ? przechodzimy do pierszego dnia nastepnego miesiaca i dodajemy reszte
				temp_change = daysOfYear[month] - daysOfYear[month - 1] + 1 +1 - temp.day; //tyle ile mamy dodac by dojsc do 1szego nastepnego miesiaca
				temp.day = 1;
				temp.month++;
				temp.yearDay += temp_change;
				temp.weekDay = (temp.weekDay + temp_change) % 7;
				number -= temp_change;
				temp = temp + number;
				return temp;
			}
			else {
				temp.day += number; //zmieniamy dzien w miesiacu
				temp.yearDay += number; //zmieniamy dzien w roku
				temp.weekDay = (temp.weekDay + number) % 7; //zmieniamy dzien tygodnia
				return temp;
			}
		}
		else {  
			if (temp_days > (daysOfYear[month] - daysOfYear[month - 1])) { //sprawdzamy z liczba dni miesiaca
				temp_change = daysOfYear[month] - daysOfYear[month - 1] + 1 - temp.day; //tyle ile mamy dodac by dojsc do 1szego nastepnego miesiaca
				temp.day = 1;
				temp.month++;
				temp.yearDay += temp_change;
				temp.weekDay = (temp.weekDay + temp_change) % 7;
				number -= temp_change;
				temp = temp + number;
				return temp;
			}
			else {
				temp.day += number; //zmieniamy dzien w miesiacu
				temp.yearDay += number; //zmieniamy dzien w roku
				temp.weekDay = (temp.weekDay + number) % 7; //zmieniamy dzien tygodnia
				return temp;
			}
		}
	}
	else {
		if (temp_days > (daysOfYear[month] - daysOfYear[month - 1])) { //sprawdzamy z liczba dni miesiaca
			temp_change = daysOfYear[month] - daysOfYear[month - 1] + 1 - temp.day; //tyle ile mamy dodac by dojsc do 1szego nastepnego miesiaca
			temp.day = 1;
			temp.month++;
			temp.yearDay += temp_change;
			temp.weekDay = (temp.weekDay + temp_change) % 7;
			number -= temp_change;
			temp = temp + number;
			return temp;
		}
		else {
			temp.day += number; //zmieniamy dzien w miesiacu
			temp.yearDay += number; //zmieniamy dzien w roku
			temp.weekDay = (temp.weekDay + number) % 7; //zmieniamy dzien tygodnia
			return temp;
		}
	}
}
	else { //gdy dwunasty miesiac
		if (temp_days > (365 - daysOfYear[month - 1])) {
			temp_change = daysOfYear[month] - daysOfYear[month - 1] + 1 - temp.day; //tyle ile mamy dodac by dojsc do 1szego nastepnego miesiaca
			temp.day = 1;
			temp.month = 1;
			temp.year++;
			temp.yearDay = 1;
			temp.weekDay = (temp.weekDay + temp_change) % 7;
			number -= temp_change;
			temp = temp + number;
			return temp;
		}
		else {
			temp.day += number; //zmieniamy dzien w miesiacu
			temp.yearDay += number; //zmieniamy dzien w roku
			temp.weekDay = (temp.weekDay + number) % 7; //zmieniamy dzien tygodnia
			return temp;
		}
	}
}

Date Date::operator--(int number) {
	Date temp = *this;
	if (day != 1) { //gdy to nie jest pierwszy dzien
		day--;
		yearDay--;
		previousWeekDay();
	}
	else { //gdy pierwszy dzien miesiaca
		if (month == 1) { //gdy pierwszy miesiac
			month = 12;
			year--;
			if (isLeapYear(year)) {
				yearDay = 366;
			}
			else {
				yearDay = 365;
			}
			day = 365 - daysOfYear[month - 1];
		}
		else { //gdy nie pierwszy miesiac
			month--;
			yearDay--;
			day = daysOfYear[month] - daysOfYear[month - 1];
			if (month == 2) { //gdy luty to jeden dzien wiecej
				day++;
			}
		}
	}
	return temp;
}

std::string Date::getWeekDayName() {
	return daysOfWeek[weekDay];
}

std::istream &operator>>(std::istream &s, Date &d) {
	s >> d.day;
	s.ignore();
	s >> d.month;
	s.ignore();
	s >> d.year;

	Date temp(d.day,d.month,d.year);
	d = temp;

	return s;
}