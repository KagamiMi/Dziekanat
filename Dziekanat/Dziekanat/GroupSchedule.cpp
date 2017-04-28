#include "GroupSchedule.h"


GroupSchedule::GroupSchedule(Date startingDate, Date endingDate, int groupNumber, int groupSemester, std::string groupSpecialization):
Schedule(startingDate, endingDate), groupNumber(groupNumber), groupSemester(groupSemester), groupSpecialization(groupSpecialization)
{
}


GroupSchedule::~GroupSchedule()
{
}

int GroupSchedule::information(std::ostream &s) {
	s << groupSpecialization << ", semestr " << groupSemester << ", grupa " << groupNumber;
	return 1;
}

bool GroupSchedule::operator==(GroupSchedule group) {
	if (groupSpecialization == group.groupSpecialization) {
		if (groupSemester == group.groupSemester) {
			if (groupNumber == group.groupNumber) {
				return true;
			}
		}
	}
	return false;
}

bool GroupSchedule::compare(GroupSchedule g1, GroupSchedule g2) { //czy g1 < g2
	if (g1.groupSpecialization < g2.groupSpecialization) {
		if (g1.groupSemester < g2.groupSemester) {
			if (g1.groupNumber < g2.groupSemester) {
				return true;
			}
		}
	}
	return false;
}

Lesson GroupSchedule::getLesson() {
	system("cls");

	std::cin.clear();
	std::cin.sync();

	std::string name;
	std::string type;
	Time *start;
	Time *end;
	int hour, minutes;

	int classroom;
	std::string teacherName;
	std::string teacherSurname;

	int groupNumber = this->groupNumber;
	int groupSemester = this->groupSemester;
	std::string groupSpecialization = this->groupSpecialization;

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
	std::cout << "Podaj numer sali:";
	std::cin >> classroom;

	std::cout.width(45);
	std::cout << "Podaj imie nauczyciela:";
	std::cin >> teacherName;

	std::cout.width(45);
	std::cout << "Podaj nazwisko nauczyciela:";
	std::cin >> teacherSurname;

	try {
		Time startTime(*start);
		Time endTime(*end);
		delete start;
		delete end;
		return Lesson(name,type,startTime,endTime,classroom,teacherName,teacherSurname,groupNumber,groupSemester,groupSpecialization);
	}
	catch (WrongLessonException) {
		throw;
	}
}