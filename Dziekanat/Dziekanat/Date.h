#pragma once
#include <iostream>
#include <string>
#include "WrongDateException.h"
class Date
{
	int day;
	int month;
	int year;
	int yearDay; //dzien roku
	int weekDay; //dzien tygodnia zakres 0-6
	static const std::string daysOfWeek[7];
	static const int daysOfYear[12];
	void nextWeekDay(); //zwieksza dzien tygodnia o jeden, do u¿ywania w operator++
	void previousWeekDay(); //zmniejsza dzien tygodnia o jeden, do uzywania w operator--;
public:
	Date();
	Date(int day, int month, int year);
	~Date();
	Date operator+(int number); //dodaje iloœæ dni
	Date operator++(int number); //zwraca obiekt przed inkrementacja, zwiêksza obecny obiekt o jeden dzieñ
	Date operator--(int number);
	bool operator==(Date date); //do porownywania
	bool isLeapYear(int _year);
	bool operator<=(Date date);
	int operator-(Date date);
	friend std::ostream &operator<<(std::ostream &s, const Date &d); //do plikow
	friend std::istream &operator>>(std::istream &s, Date &d); //do plików
	std::string getWeekDayName();
	int getWeekDay();
};

