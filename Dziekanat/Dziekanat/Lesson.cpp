#include "Lesson.h"

Lesson::Lesson(std::string _name, std::string _type, Time _start, Time _end, int _classroom, std::string _teacherName, std::string _teacherSurname,
	int _groupNumber, int _groupSemester, std::string _groupSpecialization)
{
	if (_end <= _start) {
		throw WrongLessonException();
	}
	name = _name;
	type = _type;
	start = _start;
	end = _end;
	classroom = _classroom;
	teacherName = _teacherName;
	teacherSurname = _teacherSurname;
	groupNumber = _groupNumber;
	groupSemester = _groupSemester;
	groupSpecialization = _groupSpecialization;
	
}


Lesson::~Lesson()
{
}

Time Lesson::startTime() {
	return start;
}

Time Lesson::endTime() {
	return end;
}

bool Lesson::operator==(Lesson lesson) {
	return ((name == lesson.name) && (type == lesson.type) && (start == lesson.start) && (end == lesson.end) && 
		(classroom == lesson.classroom) && (teacherName == lesson.teacherName) && (teacherSurname == lesson.teacherSurname) &&
		(groupNumber == lesson.groupNumber) && (groupSemester == lesson.groupSemester) && (groupSpecialization == lesson.groupSpecialization));
}

std::ostream & operator<<(std::ostream &s, const Lesson &l) {
	s << "lesson " << l.start << " " << l.end << " " << l.name << " " << l.type << " " << l.classroom << " " << l.teacherName << " " << l.teacherSurname <<
		" " << l.groupNumber << " " << l.groupSemester << " " << l.groupSpecialization;
	return s;
}

void Lesson::write(std::ostream &s,int schedule) { //w wypisywaniuw wszystkich lekcji
	//std::cout << l << std::endl;
	s << name << std::endl << type << std::endl << start << " - " << end << std::endl;
	switch (schedule) {
	case 1: //dla grupy
		s << classroom << std::endl << teacherName << " " << teacherSurname;
		break;
	case 2: //dla sali
		s << groupSpecialization << std::endl << "sem. " << groupSemester << " gr. " << groupNumber << std::endl <<
			teacherName << " " << teacherSurname;
		break;
	case 3:
		s << classroom << std::endl << "sem. " << groupSemester << " gr. " << groupNumber;
		break;
	default:
		break;
	}
}

int Lesson::getClassroom() {
	return classroom;
}

std::string Lesson::getTeacherName() {
	return teacherName;
}

std::string Lesson::getTeacherSurname() {
	return teacherSurname;
}

int Lesson::getGroupNumber() {
	return groupNumber;
}

int Lesson::getGroupSemester() {
	return groupSemester;
}

std::string Lesson::getGroupSpecialization() {
	return groupSpecialization;
}