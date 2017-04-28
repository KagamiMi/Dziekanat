#include "Communicate.h"
#include <conio.h>

Communicate::Communicate(std::string nameOfFile) : nameOfFile(nameOfFile)
{
	//w konstruktorze wype³niamy 
	dataFile.open(nameOfFile,std::ios::in);
	if (dataFile.good()) { //gdy plik istnieje, czyli mozemy odczytac infomacje
		//³adujemy informacje
		while (!(dataFile.eof())) {
			getSemester(dataFile);
		}
		dataFile.close();
	}
}

void Communicate::getSemester(std::fstream &dataFile) {
	std::string name;
	Date start, end;
	std::string semester;
	std::string academicYear;
	dataFile >> name;
	if (name == "semester") {
		dataFile >> start;
		dataFile >> end;
		dataFile >> academicYear;
		dataFile >> semester;
		Synchronize schedule(start, end, semester, academicYear);
		schedules.push_back(schedule);
		schedules.sort(Synchronize::compare);

		std::list<Synchronize>::iterator iter_schedule = find(schedules.begin(), schedules.end(), schedule); //iterator do wlasnie dodanego semestru
		//teraz dodajemy do tego semestru dni
		getDays(dataFile,iter_schedule);
	}
}

void Communicate::getDays(std::fstream &dataFile, std::list<Synchronize>::iterator iter_schedule) {
	std::string name;
	dataFile >> name;
	while (name != "endsemester") {
		Date date;
		dataFile >> date;
		getLessons(dataFile, iter_schedule, date);
		dataFile >> name;
	}
}

void Communicate::getLessons(std::fstream &dataFile, std::list<Synchronize>::iterator iter_schedule, Date date) {
	std::string name;
	dataFile >> name;
	while (name != "endday") {
		Time start, end;
		std::string lessonName;
		std::string lessonType;
		int classroom;
		std::string teacherName;
		std::string teacherSurname;
		int groupNumber;
		int groupSemester;
		std::string groupSpecialization;

		dataFile >> start >> end;
		dataFile >> lessonName >> lessonType;
		dataFile >> classroom;
		dataFile >> teacherName >> teacherSurname;
		dataFile >> groupNumber >> groupSemester >> groupSpecialization;

		Lesson lesson(lessonName, lessonType, start, end, classroom, teacherName, teacherSurname, groupNumber, groupSemester, groupSpecialization);

		iter_schedule->addLesson(date, lesson);

		dataFile >> name;
	}
}

Communicate::~Communicate()
{
	dataFile.open(nameOfFile, std::ios::out | std::ios::trunc); //otwieramy plik do zapisu obecnego stanu danych
	//tu wywo³ujemy zapis informacji
	if (!(schedules.empty())) { //gdy nie jest puste
		std::list<Synchronize>::iterator iter_schedule;
		for (iter_schedule = schedules.begin(); iter_schedule != schedules.end(); iter_schedule++) {
			dataFile << "semester " << *iter_schedule << std::endl;
			iter_schedule->saveDataFile(dataFile);
			dataFile << "endsemester" << std::endl;
		}
	}
	dataFile.close();
}

void Communicate::startingChoice() {
	std::list<Synchronize>::iterator iter_synchronize;
	int choice;
	while ((choice = startingMenu()) != 4) {
		switch (choice) {
		case 1: 
			 //wybranie planu na ktorym chcemy cos robic
			while ((iter_synchronize = selectSynchronize()) != schedules.end()) { //gdy nie jest to powrot
				iter_synchronize->selectChoice();
			}
			break;
		case 2: //dodanie nowego planu
			addSchedule();
			break;
		case 3:
			while ((iter_synchronize = selectSynchronize()) != schedules.end()) { //gdy nie jest to powrot
				schedules.erase(iter_synchronize);
				std::cout << "Usunieto semestr." << std::endl;
				std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
				_getch();
			}
			break;
		default:
			break;
		}
	}
}

int Communicate::startingMenu() {
	char symbol;
	int option = 1;

	while (true) { //dopoki nie chcemy wyjsc
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std:: right << ' ';
		std::cout << "SYSTEM DZIEKANAT";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;
		
		std::cout.fill(' ');
		std::cout.width(20);
		std::cout << "Wybierz semestr";
		if (option == 1) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Dodaj nowy semestr";
		if (option == 2) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Usun semestr";
		if (option == 3) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Wyjdz";
		if (option == 4) {
			std::cout << "<-" ;
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
		if (option > 4) {
			option--;
		}
	}
}

std::list<Synchronize>::iterator Communicate::selectSynchronize() { 
	std::list<Synchronize>::iterator iter_write; //do wypisywania
	std::list<Synchronize>::iterator iter_select; //do przechowywania na co obecnie wskazujemy
	char symbol;
	int option = 1, number =1;

	while (true) {
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Wybierz semestr";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		for (iter_write = schedules.begin(); iter_write != schedules.end(); iter_write++, number++) {
			//std::cout.width(20);
			iter_write->information(); //wypisanie informacji o planie
			if (option == number) { //gdy wskazujemy na dany plan
				std::cout << "\t<-" << std::endl;
				iter_select = iter_write; //zapamietanie iteratora na obecny plan
			}
			else {
				std::cout << std::endl;
			}
		}
		std::cout.width(30);
		std::cout << "Wroc";
		if (option == number) {
			std::cout << "<-";
			iter_select = schedules.end(); //gdy wracamy, ustawiamy na koniec
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
			return iter_select;
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

void Communicate::addSchedule() {
	//Date startingDate();
	//Date endingDate();
	int day, month, year;
	std::string semester;
	std::string academicYear;
	Date *startingDate;
	Date *endingDate;

	std::cin.clear();
	std::cin.sync();

	system("cls");
	std::cout.width(6);
	std::cout.fill('*');
	std::cout << std::right << ' ';
	std::cout << "Dodaj nowy semestr";
	std::cout.width(6);
	std::cout << std::left << ' ';
	std::cout << std::endl;

	std::cout.fill(' ');
	std::cout.width(40);
	std::cout << "Podaj rok akademicki:";
	std::cin >> academicYear;

	std::cout.width(40);
	std::cout << "Podaj nazwe semestru:";
	std::cin >> semester;

	std::cout.width(40);
	std::cout << "Podaj poczatkowa date (dd.mm.rrrr): ";
	std::cin >> day;
	std::cin.ignore();
	std::cin >> month;
	std::cin.ignore();
	std::cin >> year;

	try {
		startingDate = new Date(day,month,year);
	}
	catch (WrongDateException ex){
		if (ex.wrongDay) {
			std::cout << "Podano zly dzien." << std::endl;
		}
		if (ex.wrongMonth) {
			std::cout << "Podano zly miesiac." << std::endl;
		}
		if (ex.wrongYear) {
			std::cout << "Podano zly rok." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic do menu glownego." << std::endl;
		_getch();
		return;
	}

	std::cout.width(40);
	std::cout << "Podaj koncowa date (dd.mm.rrrr): ";
	std::cin >> day;
	std::cin.ignore();
	std::cin >> month;
	std::cin.ignore();
	std::cin >> year;

	try {
		endingDate = new Date(day, month, year);
	}
	catch (WrongDateException ex){
		if (ex.wrongDay) {
			std::cout << "Podano zly dzien." << std::endl;
		}
		if (ex.wrongMonth) {
			std::cout << "Podano zly miesiac." << std::endl;
		}
		if (ex.wrongYear) {
			std::cout << "Podano zly rok." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic do menu glownego." << std::endl;
		_getch();
		delete startingDate;
		return;
	}

	try {
		Synchronize schedule(*startingDate, *endingDate, semester, academicYear);
		if (schedules.empty()) {
			schedules.push_back(schedule);
		}
		else {
			std::list<Synchronize>::iterator iter = find(schedules.begin(), schedules.end(), schedule);
			if (iter == schedules.end()) {
				schedules.push_back(schedule);
			}
			else {
				std::cout << "Taki semestr juz istnieje." << std::endl;
				std::cout << "Wcisnij dowolny przycisk by wrocic do menu glownego." << std::endl;
				_getch();
				return;
			}
		}
	}
	catch (WrongScheduleException) {
		std::cout << "Data koncowa jest mniejsza od poczatkowej." << std::endl << "Sprobuj ponownie." << std::endl <<
			"Wcisnij dowolny przycisk by wrocic do menu glownego." << std::endl;
		_getch();
		delete startingDate;
		delete endingDate;
		return;
	}
	delete startingDate;
	delete endingDate;
	//posortowanie po dodaniu
	schedules.sort(Synchronize::compare);
	std::cout << "Semestr dodano." << std::endl;
	std::cout << "Wcisnij dowolny przycisk by wrocic do menu glownego." << std::endl;
	_getch();
	return;
}

void deleteSchedule(std::list<Synchronize>::iterator schedule) {

}