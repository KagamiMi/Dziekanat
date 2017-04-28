#include "Week.h"


Week::Week(Date _startingDate, Date _endingDate) : startingDate(_startingDate), endingDate(_endingDate)
{
	if ((!(_startingDate <= _endingDate)) ||((_endingDate-_startingDate)>6)) { //koniec nie moze byc przed poczatkiem i nie moze byc d³u¿szy ni¿ 7 dni
		throw WrongWeekException(1,0);
	}
	

	Date date(startingDate); //wypelnienie datami 
	while (date <= endingDate) {
		weekDays.push_back(Day(date));
		date++;
	}
}


Week::~Week()
{
}

void Week::saveDataFile(std::fstream &dataFile) {
	if (!(weekDays.empty())) {
		for (int i = 0; i < weekDays.size(); i++) {
			if (!(weekDays[i].isEmpty())) { //gdy dzien nie jest pusty
				weekDays[i].saveDataFile(dataFile);
			}
		}
	}
}

std::vector<Day>::iterator Week::getDay(int number) { 
	std::vector<Day>::iterator iter = std::find_if(weekDays.begin(), weekDays.end(), [&](Day day){return day.getWeekDay() == number; });
	if (iter == weekDays.end()) {
			throw WrongWeekException(0, 1);
	}
	return iter;
}



void Week::information(std::ostream &s) {
	s << startingDate << " - " << endingDate;
}

void Week::displayWeek(std::ostream &s, int schedule) {
	s << std::endl;
	for (int i = 0; i < weekDays.size(); i++) { //przejscie po wszystkich dniach
		if (!(weekDays[i].isEmpty())) { //gdy nie jest pusta
			s.width(20);
			s.fill('-');
			s << "-" << std::endl;
			weekDays[i].displayDay(s, schedule); //zrob

		}
	}
	s.width(20);
	s.fill('-');
	s << "-" << std::endl;
}

int Week::daysMenu() {
	char symbol;
	int option = 0;
	int number;

	while (true) { //dopoki nie chcemy wyjsc
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Wybierz dzien";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		for (number = 0; number < weekDays.size(); number++) {
			std::cout.width(20);
			std::cout << weekDays[number].getWeekDayName();
			if (option == number) { //gdy wskazujemy na dany plan
				std::cout << "<-" << std::endl;
			}
			else {
				std::cout << std::endl;
			}
		}

		symbol = _getch(); //pobieramy symbol wykonanej wlasnie akcji

		switch (symbol)
		{
		case 72: //strzalka w gore
			option--;
			break;
		case 80: //strzalka w dol
			option++;
			break;
		case 13: //enter
			system("cls");
			return option;
			break;
		default:
			break;
		}
		if (option < 0) {
			option++;
		}
		if (option >= weekDays.size()) {
			option--;
		}
	}
}

Date Week::getStart() {
	return startingDate;
}

Date Week::getEnd() {
	return endingDate;
}