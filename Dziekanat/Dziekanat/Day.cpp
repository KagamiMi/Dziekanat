#include "Day.h"
#include "Lesson.h"
#include "AddingLessonException.h"
#include <iostream>
#include <list>
#include <algorithm>

Day::Day(Date date) : date(date)
{
}


Day::~Day()
{
}

void Day::addLesson(Lesson lesson)
{
	bool possible_begin = 1, possible_end = 0; //false na poczatku
	std::list<Lesson>::iterator iter;

	if (lessonsList.empty()) { //gdy true, lista jest pusta
		lessonsList.push_back(lesson);
	}
	else { //gdy nie jest pusta, musimy przejsc po elementach czyli iterator
		for (iter = lessonsList.begin(); ((iter != lessonsList.end()) && (possible_begin && !possible_end)); iter++) {
			//zaczynamy od sprawdzenia daty startowej, czy mo¿na wstawiæ przed, possible_begin ustawione na true poczatkowo
			if (lesson.endTime() <= iter->startTime()) { //jeœli koñczy siê rowno lub przed rozpoczeciem iter
				possible_end = 1; //wtedy mo¿na wstawiæ 
			}
			if (!(possible_begin && possible_end)) {//sprawdzamy, czy warunki zgadzaja sie dla wstawienia przed obecnym iteratorem
				//jesli sie nie sprawdzaja, to sprawdzamy dalej
				possible_begin = possible_end = 0; //zerujemy zmienne
				if (lesson.startTime() >= iter->endTime()) { //jesli zaczyna sie rowno lub po rozpoczeciu iter
					possible_begin = 1;
				}
			}
		} //koniec petli for

		if (possible_begin && possible_end) { 
			iter--; //nawet gdy oba by³y dobre, to zwiêkszy³o dodatkowo o jeden na koniec petli, wiec trzeba zmniejszyc
			lessonsList.insert(iter, lesson); //wstawiamy
		}
		else if (possible_begin && (iter == lessonsList.end())) {
			lessonsList.insert(iter, lesson); //dodanie na koncu
		}
		else {
			if (iter == lessonsList.end()) { //gdy na koncu, to sprawdzamy czy possible_end zgadzalby sie
				iter--;
				if (!(lesson.endTime() <= iter->endTime())) {
					throw AddingLessonException(!possible_begin, 0);
				}
			}
			else {
				if (lesson.endTime() <= iter->startTime()) { //sprawdzamy czy possible_end zgadzalby sie
					iter--;
					if (!(lesson.endTime() <= iter->endTime())) { //sprawdzamy, czy bylby po najwczesniejszym dobrym possible_begin
						throw AddingLessonException(!possible_begin, 0);
					}
				}
			}
			throw AddingLessonException(!possible_begin,!possible_end);
		}
	}
	
}

std::list<Lesson>::iterator Day::searchLesson(Lesson lesson) { //wyszukanie lekcji, jesli istnieje zwrocenie iterator na nia, jesli nie wyjatek
	if (lessonsList.empty()) {
		throw SearchingLessonException();
	}
	std::list<Lesson>::iterator iter = std::find(lessonsList.begin(), lessonsList.end(), lesson);
	if (iter == lessonsList.end()) {
		throw SearchingLessonException();
	}
	return iter;
}

void Day::deleteLesson(Lesson lesson) {
	std::list<Lesson>::iterator iter;

	try {
		iter = searchLesson(lesson); //próba znalezienia elementu
	}
	catch (SearchingLessonException) { //gdy nie udalo sie znalezc, re-throw
		throw;
	}

	lessonsList.erase(iter); //gdy udalo sie znalezc, usuwamy, zwracamy iterator do nastepnego elementu
}

void Day::displayDay(std::ostream &s, int schedule) {
	s << date.getWeekDayName() << std::endl;
	s.width(20);
	s.fill('-');
	s << "-" << std::endl;
	for (std::list<Lesson>::iterator iter = lessonsList.begin(); iter != lessonsList.end(); iter++) {
		iter->write(s,schedule);
		s << std::endl << std::endl;
	}

}

int Day::getWeekDay() {
	return date.getWeekDay();
}

std::string Day::getWeekDayName() {
	return date.getWeekDayName();
}

bool Day::isEmpty() {
	return lessonsList.empty();
}

Date Day::getDate() {
	return date;
}

void Day::saveDataFile(std::fstream &dataFile) {
	dataFile << "day " << date << std::endl;
	std::list<Lesson>::iterator iter;
	for (iter = lessonsList.begin(); iter != lessonsList.end(); iter++) {
		dataFile << *iter << std::endl;
	}
	dataFile << "endday" << std::endl;
}