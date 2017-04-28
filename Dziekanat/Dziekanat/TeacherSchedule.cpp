#include "TeacherSchedule.h"


TeacherSchedule::TeacherSchedule(Date startingDate, Date endingDate, std::string teacherName, std::string teacherSurname) : Schedule(startingDate,endingDate),
teacherName(teacherName), teacherSurname(teacherSurname)
{
}


TeacherSchedule::~TeacherSchedule()
{
}

int TeacherSchedule::information(std::ostream &s) {
	s << teacherName << " " << teacherSurname;
	return 3;
}

bool TeacherSchedule::operator==(TeacherSchedule teacher) {
	if (teacherSurname == teacher.teacherSurname) {
		if (teacherName == teacher.teacherName) {
			return true;
		}
	}
	return false;
}

bool TeacherSchedule::compare(TeacherSchedule t1, TeacherSchedule t2) {
	if (t1.teacherSurname < t2.teacherSurname) {
		if (t1.teacherName < t2.teacherName) {
			return true;
		}
	}
	return false;
}

Lesson TeacherSchedule::getLesson() {
	system("cls");

	std::cin.clear();
	std::cin.sync();

	std::string name;
	std::string type;
	Time *start;
	Time *end;
	int hour, minutes;

	int classroom;

	std::string teacherName = this->teacherName;
	std::string teacherSurname = this->teacherName;
	
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
	std::cout << "Podaj numer sali:";
	std::cin >> classroom;

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
