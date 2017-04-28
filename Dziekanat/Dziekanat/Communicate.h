#pragma once
#include "Synchronize.h"
#include <fstream>
class Communicate
{
	std::string nameOfFile; //nazwa pliku z ktorego bedziemy odczytywac/zapisywac dane
	std::fstream dataFile; //plik przechowuj¹cy dane
	std::list<Synchronize> schedules; //zawiera ró¿ne plany
public:
	Communicate(std::string nameOfFile);
	~Communicate();
	int startingMenu(); //komunikacja z u¿ytkownikiem, zwraca numer akcji do wykonania
	void startingChoice(); //przechodzi do czynnosci wybranej przez uzytkownika
	std::list<Synchronize>::iterator selectSynchronize();
	void addSchedule(); //jakos alfabetycznie poustawiac
	void getSemester(std::fstream &dataFile);
	void getDays(std::fstream &dataFile, std::list<Synchronize>::iterator iter_schedule);
	void getLessons(std::fstream &dataFile, std::list<Synchronize>::iterator iter_schedule,Date date);
};

