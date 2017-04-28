#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "Date.h"
#include "Day.h"
#include "Lesson.h"
#include "Time.h"
//#include <vld.h> sprawdzanie wyciekow pamieci
#include "Week.h"
#include "Schedule.h"
#include "Communicate.h"
using namespace std;

int main() {
	Communicate temp("textDatabase.txt");

	temp.startingChoice();
	cout << "Koniec!" << endl;
	getchar();
	return 0;
}

