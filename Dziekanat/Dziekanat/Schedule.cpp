#include "Schedule.h"
#include "WrongScheduleException.h"


Schedule::Schedule(Date _startingDate, Date _endingDate) : startingDate(_startingDate), endingDate(_endingDate)
{
	
	//podzieliæ na 7-diowe tygodnie, albo mniej-dniowe
	Date startWeek(startingDate), endWeek(startingDate+6); //dla normalnych 7-dniowych tygodni
	Date end(endingDate);
	
	if (startingDate.getWeekDay() == 0) {//gdy zaczynamy od poniedzialku
		weeks.push_back(Week(startWeek,endWeek));
		startWeek = startWeek + 7;
		endWeek = endWeek + 7;
	}
	else { //gdy zaczynamy od innego dnia
		endWeek = startWeek;
		while (endWeek.getWeekDay() != 6) { //ustawiamy endWeek na ostatni dzien tygodnia
			endWeek++;
		}
		weeks.push_back(Week(startWeek,endWeek)); //wstawiamy mniejszy tydzien
		startWeek = endWeek + 1;
		endWeek = endWeek + 7;
	}

	if (endingDate.getWeekDay() == 6) {//gdy konczymy na niedzieli

	}
	else { //gdy konczymy na innym dniu
		//wtedy musimy ostatni tydzien ustalic wczesniej 
		while (end.getWeekDay() != 6) {
			end--;
		}
	}

	while (!(endWeek == end)) { //leca normalne tygodnie
		weeks.push_back(Week(startWeek, endWeek));
		startWeek = startWeek + 7;
		endWeek = endWeek + 7;
	}
	weeks.push_back(Week(startWeek, endWeek)); //dodajemy ostatni normalny tydzien
	
	if (!(end == endingDate)) {
		startWeek = startWeek + 7;
		weeks.push_back(Week(startWeek, endingDate)); //dodajemy ostatni niepelny tydzien
	}
}

void Schedule::saveDataFile(std::fstream &dataFile) {
	if (!(weeks.empty())) {
		for (int i = 0; i < weeks.size(); i++) {
			weeks[i].saveDataFile(dataFile);
		}
	}
}


Schedule::~Schedule()
{
}

int Schedule::selectMenu() {
	char symbol;
	int option = 1;

	while (true) { //dopoki nie chcemy wyjsc
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		information(std::cout);
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		std::cout.width(20);
		std::cout << "Wyswietl plan";
		if (option == 1) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Zapisz plan do pliku";
		if (option == 2) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Dodaj zajecia";
		if (option == 3) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Usun zajecia";
		if (option == 4) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Wroc";
		if (option == 5) {
			std::cout << "<-";
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
		if (option < 1) {
			option++;
		}
		if (option > 5) {
			option--;
		}
	}
}

std::vector<Week>::iterator Schedule::weekMenu() {
	std::vector<Week>::iterator iter_write;
	std::vector<Week>::iterator iter_week;
	char symbol;
	int option = 1, number = 1;

	while (true) {
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Wybierz tydzien";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		for (iter_write = weeks.begin(); iter_write != weeks.end(); iter_write++, number++) {
			//std::cout.width(20);
			iter_write->information(std::cout); //wypisanie informacji o planie
			if (option == number) { //gdy wskazujemy na dany plan
				std::cout << "\t<-" << std::endl;
				iter_week = iter_write; //zapamietanie iteratora na obecny plan
			}
			else {
				std::cout << std::endl;
			}
		}
		std::cout.width(20);
		std::cout << "Wroc";
		if (option == number) {
			std::cout << "<-";
			iter_week = weeks.end(); //gdy wracamy, ustawiamy na koniec
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
			return iter_week;
			break;
		default:
			break;
		}
		if (option < 1) {
			option++;
		}
		if (option > number) {
			option--;
		}
		number = 1; //wracamy numer do wypisywania na pierwszy
	}
}

void Schedule::saveSchedule(std::vector<Week>::iterator week) {
	system("cls");
	std::cin.clear();
	std::cin.sync();
	std::fstream outputFile;
	std::string nameFile;
	std::cout << "Podaj nazwe pliku z rozszerzeniem do ktorego chcesz zapisac plan:" << std::endl;
	std::cin >> nameFile;
	outputFile.open(nameFile,std::ios::out);
	week->displayWeek(outputFile,information(outputFile));
	outputFile.close();
}

std::vector<Week>::iterator Schedule::getEndIterator() {
	return weeks.end();
}


void Schedule::addLesson(Date startWeek, int dayNumber, Lesson lesson) {
	std::vector<Week>::iterator week = find_if(weeks.begin(), weeks.end(), [&](Week w1)->bool{return (w1.getStart() == startWeek); }); //bierzemy odpowiedni tydzien
	std::vector<Day>::iterator day = week->getDay(dayNumber); //dostajemy sie do dnia
	try {
		day->addLesson(lesson);
	}
	catch (AddingLessonException exc) {
		throw exc;
	}
}

void Schedule::deleteLesson(Date startWeek, int dayNumber, Lesson lesson) {
	std::vector<Week>::iterator week = find_if(weeks.begin(), weeks.end(), [&](Week w1)->bool{return (w1.getStart() == startWeek); }); //bierzemy odpowiedni tydzien
	std::vector<Day>::iterator day = week->getDay(dayNumber); //dostajemy sie do dnia
	try {
		day->deleteLesson(lesson);
	}
	catch (SearchingLessonException exc) {
		throw exc;
	}
}

void Schedule::addLesson(Date date, Lesson lesson) {
	//wyszukac date w tygodniach i dodac do dnia
	std::vector<Week>::iterator week;
	bool found = false;
	for (week = weeks.begin(); (week != weeks.end() && !found); week++) {
		if (week->getStart() <= date) {
			if (date <= week->getEnd()) {
				found = true;
			}
		}
	}
	week--;
	std::vector<Day>::iterator day = week->getDay(date.getWeekDay()); //dostajemy sie do dnia do ktorego chcemy dodac
	day->addLesson(lesson);
}

int Schedule::size() {
	return weeks.size();
}