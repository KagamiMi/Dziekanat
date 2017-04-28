#include "ClassroomSchedule.h"


ClassroomSchedule::ClassroomSchedule(Date startingDate, Date endingDate, int classroom) : Schedule(startingDate, endingDate), classroom(classroom)
{
}


ClassroomSchedule::~ClassroomSchedule()
{
}

int ClassroomSchedule::information(std::ostream &s) {
	s << classroom;
	return 2;
}

bool ClassroomSchedule::operator==(ClassroomSchedule classroom) {
	if (this->classroom == classroom.classroom) {
		return true;
	}
	return false;
}

bool ClassroomSchedule::compare(ClassroomSchedule c1, ClassroomSchedule c2) { //czy c1 < c2
	if (c1.classroom < c2.classroom) {
		return true;
	}
	return false;
}

Lesson ClassroomSchedule::getLesson() {
	system("cls");

	std::cin.clear();
	std::cin.sync();

	std::string name;
	std::string type;
	Time *start;
	Time *end;
	int hour, minutes;

	int classroom = this->classroom;

	std::string teacherName;
	std::string teacherSurname;
	int groupNumber;
	int groupSemester;
	std::string groupSpecialization;

	std::cout.width(45);
	std::cout << "Podaj nazwe zajec:";
	std::cin >> name;

	std::cout.width(45);
	std::cout << "Podaj typ zajec:";
	std::cin >> type;

	std::cout.width(45);
	std::cout << "Podaj godzine rozpoczecia zajec (hh:mm):";
	std::cin >> hour;
	std::cin.ignore();
	std::cin >> minutes;

	try {
		start = new Time(hour, minutes);
	}
	catch (WrongTimeException exc) {
		throw exc;
	}

	std::cout.width(45);
	std::cout << "Podaj godzine zakonczenia zajec (hh:mm):";
	std::cin >> hour;
	std::cin.ignore();
	std::cin >> minutes;

	try {
		end = new Time(hour, minutes);
	}
	catch (WrongTimeException exc) {
		delete start;
		throw exc;
	}

	std::cout.width(45);
	std::cout << "Podaj imie nauczyciela:";
	std::cin >> teacherName;

	std::cout.width(45);
	std::cout << "Podaj nazwisko nauczyciela:";
	std::cin >> teacherSurname;

	std::cout.width(45);
	std::cout << "Podaj kierunek grupy:";
	std::cin >> groupSpecialization;

	std::cout.width(45);
	std::cout << "Podaj semestr grupy:";
	std::cin >> groupSemester;

	std::cout.width(45);
	std::cout << "Podaj numer grupy:";
	std::cin >> groupNumber;

	try {
		Time startTime(*start);
		Time endTime(*end);
		delete start;
		delete end;
		return Lesson(name, type, startTime, endTime, classroom, teacherName, teacherSurname, groupNumber, groupSemester, groupSpecialization);
	}
	catch (WrongLessonException) {
		throw;
	}
}