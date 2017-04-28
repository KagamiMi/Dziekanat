#include "Synchronize.h"


Synchronize::Synchronize(Date startingDate, Date endingDate, std::string semester, std::string academicYear) : startingDate(startingDate),
endingDate(endingDate), semester(semester), academicYear(academicYear)
{
	if (!(startingDate <= endingDate)) {
		throw WrongScheduleException();
	}
}


Synchronize::~Synchronize()
{
}

std::ostream &operator<<(std::ostream &s, const Synchronize &synchronize) {
	s << synchronize.startingDate << " " << synchronize.endingDate << " " << synchronize.academicYear << " " << synchronize.semester;
	return s;
}

void Synchronize::saveDataFile(std::fstream &dataFile) {
	if (!(classrooms.empty())) {
		std::list<ClassroomSchedule>::iterator iter;
		for (iter = classrooms.begin(); iter != classrooms.end(); iter++) {
			iter->saveDataFile(dataFile);
		}
	}
}

void Synchronize::information() {
	std::cout << "Rok: " << academicYear << " Semestr: " << semester;
}

bool Synchronize::compare(Synchronize s1, Synchronize s2) { //czy s1 < s2
	if (s1.academicYear < s2.academicYear) {
		return true;
	}
	else if (s1.academicYear == s2.academicYear) {
		if (s1.semester < s2.semester) {
			return true;
		}
	}
	return false;
}

int Synchronize::selectMenu() {
	char symbol;
	int option = 1;

	while (true) { //dopoki nie chcemy wyjsc
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		information();
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		std::cout.width(20);
		std::cout << "Plany grup";
		if (option == 1) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}
		std::cout.fill(' ');
		std::cout.width(20);
		std::cout << "Plany sal";
		if (option == 2) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Plany nauczycieli";
		if (option == 3) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(20);
		std::cout << "Wroc";
		if (option == 4) {
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
		if (option > 4) {
			option--;
		}
	}
}

void Synchronize::selectChoice() {
	int option;

	while ((option = selectMenu()) != 4) { //gdy nie koniec
		switch (option) {
		case 1: //grupa - czy chcemy dodac nowa, czy chcemy wybrac z istniejacych
			groupOption();
			break;
		case 2: //sala 
			classroomOption();
			break;
		case 3: //nauczyciel
			teacherOption();
			break;
		default:
			break;
		}
	}
}

std::list<GroupSchedule>::iterator Synchronize::selectGroup() {
	std::list<GroupSchedule>::iterator iter_write;
	std::list<GroupSchedule>::iterator iter_group;
	char symbol;
	int option = 1, number = 1;

	while (true) {
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Wybierz plan grupy";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		for (iter_write = groups.begin(); iter_write != groups.end(); iter_write++, number++) {
			//std::cout.width(20);
			iter_write->information(std::cout); //wypisanie informacji o planie
			if (option == number) { //gdy wskazujemy na dany plan
				std::cout << "\t<-" << std::endl;
				iter_group = iter_write; //zapamietanie iteratora na obecny plan
			}
			else {
				std::cout << std::endl;
			}
		}
		std::cout.width(20);
		std::cout << "Wroc";
		if (option == number) {
			std::cout << "<-";
			iter_group = groups.end(); //gdy wracamy, ustawiamy na koniec
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
			return iter_group;
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

std::list<ClassroomSchedule>::iterator Synchronize::selectClassroom() {
	std::list<ClassroomSchedule>::iterator iter_write;
	std::list<ClassroomSchedule>::iterator iter_classroom;
	char symbol;
	int option = 1, number = 1;

	while (true) {
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Wybierz plan sali";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		for (iter_write = classrooms.begin(); iter_write != classrooms.end(); iter_write++, number++) {
			//std::cout.width(20);
			iter_write->information(std::cout); //wypisanie informacji o planie
			if (option == number) { //gdy wskazujemy na dany plan
				std::cout << "\t<-" << std::endl;
				iter_classroom = iter_write; //zapamietanie iteratora na obecny plan
			}
			else {
				std::cout << std::endl;
			}
		}
		std::cout.width(20);
		std::cout << "Wroc";
		if (option == number) {
			std::cout << "<-";
			iter_classroom = classrooms.end(); //gdy wracamy, ustawiamy na koniec
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
			return iter_classroom;
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

std::list<TeacherSchedule>::iterator Synchronize::selectTeacher() {
	std::list<TeacherSchedule>::iterator iter_write;
	std::list<TeacherSchedule>::iterator iter_teacher;
	char symbol;
	int option = 1, number = 1;

	while (true) {
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Wybierz plan nauczyciela";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		for (iter_write = teachers.begin(); iter_write != teachers.end(); iter_write++, number++) {
			//std::cout.width(20);
			iter_write->information(std::cout); //wypisanie informacji o planie
			if (option == number) { //gdy wskazujemy na dany plan
				std::cout << "\t<-" << std::endl;
				iter_teacher = iter_write; //zapamietanie iteratora na obecny plan
			}
			else {
				std::cout << std::endl;
			}
		}
		std::cout.width(20);
		std::cout << "Wroc";
		if (option == number) {
			std::cout << "<-";
			iter_teacher = teachers.end(); //gdy wracamy, ustawiamy na koniec
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
			return iter_teacher;
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

int Synchronize::groupMenu() {
	char symbol;
	int option = 1;

	while (true) { //dopoki nie chcemy wyjsc
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Plany grup";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		std::cout.width(25);
		std::cout << "Wybierz plan grupy";
		if (option == 1) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(25);
		std::cout << "Dodaj nowy plan grupy";
		if (option == 2) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(25);
		std::cout << "Wroc";
		if (option == 3) {
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
		if (option > 3) {
			option--;
		}
	}
}

int Synchronize::classroomMenu() {
	char symbol;
	int option = 1;

	while (true) { //dopoki nie chcemy wyjsc
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Plany sal";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		std::cout.width(25);
		std::cout << "Wybierz plan sali";
		if (option == 1) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(25);
		std::cout << "Dodaj nowy plan sali";
		if (option == 2) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(25);
		std::cout << "Wroc";
		if (option == 3) {
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
		if (option > 3) {
			option--;
		}
	}
}

int Synchronize::teacherMenu() {
	char symbol;
	int option = 1;

	while (true) { //dopoki nie chcemy wyjsc
		system("cls");
		std::cout.width(6);
		std::cout.fill('*');
		std::cout << std::right << ' ';
		std::cout << "Plany nauczycieli";
		std::cout.width(6);
		std::cout << std::left << ' ';
		std::cout << std::endl;

		std::cout.fill(' ');
		std::cout.width(30);
		std::cout << "Wybierz plan nauczyciela";
		if (option == 1) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(30);
		std::cout << "Dodaj nowy plan nauczyciela";
		if (option == 2) {
			std::cout << "<-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cout.width(30);
		std::cout << "Wroc";
		if (option == 3) {
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
		if (option > 3) {
			option--;
		}
	}
}

void Synchronize::groupOption() {
	int option;
	std::list<GroupSchedule>::iterator group;
	while ((option = groupMenu()) != 3) {
		switch (option) {
		case 1:
			while ((group = selectGroup()) != groups.end()) {
				selectScheduleChoice(group); 
				//tutaj musimy wrocic bo robimy dla wszystkiego
				//mamy grupe z ktora chcemy cos zrobic -> CD.
			}
			break;
		case 2:
			addGroup();
			break;
		default:
			break;
		}
	}
}

void Synchronize::classroomOption() {
	int option;
	std::list<ClassroomSchedule>::iterator classroom;
	while ((option = classroomMenu()) != 3) {
		switch (option) {
		case 1:
			while ((classroom = selectClassroom()) != classrooms.end()) {
				selectScheduleChoice(classroom);
				//mamy klase z ktora chcemy cos zrobic -> CD.
			}
			break;
		case 2:
			addClassroom();
			break;
		default:
			break;
		}
	}
}

void Synchronize::teacherOption() {
	int option;
	std::list<TeacherSchedule>::iterator teacher;
	while ((option = teacherMenu()) != 3) {
		switch (option) {
		case 1:
			while ((teacher = selectTeacher()) != teachers.end()) {
				//mamy nauczyciela z ktora chcemy cos zrobic -> CD.
				selectScheduleChoice(teacher);
			}
			break;
		case 2:
			addTeacher();
			break;
		default:
			break;
		}
	}
}

void Synchronize::addGroup() {
	int groupNumber;
	int groupSemester;
	std::string groupSpecialization;

	std::cin.clear();
	std::cin.sync();

	system("cls");
	std::cout.width(6);
	std::cout.fill('*');
	std::cout << std::right << ' ';
	std::cout << "Dodaj nowy plan grupy";
	std::cout.width(6);
	std::cout << std::left << ' ';
	std::cout << std::endl;

	std::cout.fill(' ');
	std::cout.width(40);
	std::cout << "Podaj kierunek grupy:";
	std::cin >> groupSpecialization;

	std::cout.width(40);
	std::cout << "Podaj semestr grupy:";
	std::cin >> groupSemester;
	
	std::cout.width(40);
	std::cout << "Podaj numer grupy:";
	std::cin >> groupNumber;


	if (existGroup(GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization))) {
		std::cout << "Taka grupa juz istnieje." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	else {
		groups.push_back(GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization)); //dodanie jesli nie istnieje
		groups.sort(GroupSchedule::compare); //posortowanie
	}

}

void Synchronize::addClassroom() {
	int classroom;

	std::cin.clear();
	std::cin.sync();

	system("cls");
	std::cout.width(6);
	std::cout.fill('*');
	std::cout << std::right << ' ';
	std::cout << "Dodaj nowy plan sali";
	std::cout.width(6);
	std::cout << std::left << ' ';
	std::cout << std::endl;

	std::cout.fill(' ');
	std::cout.width(40);
	std::cout << "Podaj numer sali:";
	std::cin >> classroom;

	if (existClassroom(ClassroomSchedule(startingDate, endingDate, classroom))) {
		std::cout << "Taka sala juz istnieje." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	else {
		classrooms.push_back(ClassroomSchedule(startingDate, endingDate, classroom)); //dodanie jesli nie istnieje
		classrooms.sort(ClassroomSchedule::compare); //posortowanie
	}
}

void Synchronize::addTeacher() {
	std::string teacherName;
	std::string teacherSurname;

	std::cin.clear();
	std::cin.sync();

	system("cls");
	std::cout.width(6);
	std::cout.fill('*');
	std::cout << std::right << ' ';
	std::cout << "Dodaj nowy plan nauczyciela";
	std::cout.width(6);
	std::cout << std::left << ' ';
	std::cout << std::endl;

	std::cout.fill(' ');
	std::cout.width(40);
	std::cout << "Podaj imie nauczyciela:";
	std::cin >> teacherName;

	std::cout.width(40);
	std::cout << "Podaj nazwisko nauczyciela:";
	std::cin >> teacherSurname;

	if (existTeacher(TeacherSchedule(startingDate, endingDate, teacherName,teacherSurname))) {
		std::cout << "Taki nauczyciel juz istnieje." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	else {
		teachers.push_back(TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname)); //dodanie jesli nie istnieje
		teachers.sort(TeacherSchedule::compare); //posortowanie
	}
}

bool Synchronize::existGroup(GroupSchedule group) {
	std::list<GroupSchedule>::iterator find;
	find = std::find(groups.begin(),groups.end(),group);
	if (find == groups.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool Synchronize::existClassroom(ClassroomSchedule classroom) {
	std::list<ClassroomSchedule>::iterator find;
	find = std::find(classrooms.begin(), classrooms.end(), classroom);
	if (find == classrooms.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool Synchronize::existTeacher(TeacherSchedule teacher) {
	std::list<TeacherSchedule>::iterator find;
	find = std::find(teachers.begin(), teachers.end(), teacher);
	if (find == teachers.end()) {
		return false;
	}
	else {
		return true;
	}
}

void Synchronize::selectScheduleChoice(std::list<GroupSchedule>::iterator group) {
	std::vector<Week>::iterator week;
	int choice;

	while ((choice = group->selectMenu()) != 5) {
		switch (choice) {
		case 1: //wyswietlanie planu
			while ((week = group->weekMenu()) != group->getEndIterator()) {
				system("cls");
				week->displayWeek(std::cout, group->information(std::cout));	//wyswietlenie planu dla week, zaleznie od schedule...
				std::cout << "Nacisnij dowolny klawisz aby wrocic" << std::endl;
				_getch();
			}
			break;
		case 2: //zapisywanie planu do pliku
			while ((week = group->weekMenu()) != group->getEndIterator()) {
				system("cls");
				group->saveSchedule(week);
				std::cout << "Plan zapisany.\nNacisnij dowolny klawisz aby wrocic" << std::endl;
				_getch();
			}
			break;
		case 3:
			//dodaj zajecia
			while ((week = group->weekMenu()) != group->getEndIterator()) {
				system("cls");
				addLesson(group,week); 
			}
			break;
		case 4:
			while ((week = group->weekMenu()) != group->getEndIterator()) {
				system("cls");
				deleteLesson(group, week); 
			}
			//usun zajecia
			break;
		}
	}
}

void Synchronize::selectScheduleChoice(std::list<ClassroomSchedule>::iterator classroom) {
	std::vector<Week>::iterator week;
	int choice;

	while ((choice = classroom->selectMenu()) != 5) {
		switch (choice) {
		case 1: //wyswietlanie planu
			while ((week = classroom->weekMenu()) != classroom->getEndIterator()) {
				system("cls");
				week->displayWeek(std::cout, classroom->information(std::cout));	//wyswietlenie planu dla week, zaleznie od schedule...
				std::cout << "Nacisnij dowolny klawisz aby wrocic" << std::endl;
				_getch();
			}
			break;
		case 2: //zapisywanie planu do pliku
			while ((week = classroom->weekMenu()) != classroom->getEndIterator()) {
				system("cls");
				classroom->saveSchedule(week);
				std::cout << "Plan zapisany.\nNacisnij dowolny klawisz aby wrocic" << std::endl;
				_getch();
			}
			break;
		case 3:
			//dodaj zajecia
			while ((week = classroom->weekMenu()) != classroom->getEndIterator()) {
				system("cls");
				addLesson(classroom, week); //
			}
			break;
		case 4:
			//usun zajecia
			while ((week = classroom->weekMenu()) != classroom->getEndIterator()) {
				system("cls");
				deleteLesson(classroom, week); 
			}
			break;
		}
	}
}

void Synchronize::selectScheduleChoice(std::list<TeacherSchedule>::iterator teacher) {
	std::vector<Week>::iterator week;
	int choice;

	while ((choice = teacher->selectMenu()) != 5) {
		switch (choice) {
		case 1: //wyswietlanie planu
			while ((week = teacher->weekMenu()) != teacher->getEndIterator()) {
				system("cls");
				week->displayWeek(std::cout, teacher->information(std::cout));	//wyswietlenie planu dla week, zaleznie od schedule...
				std::cout << "Nacisnij dowolny klawisz aby wrocic" << std::endl;
				_getch();
			}
			break;
		case 2: //zapisywanie planu do pliku
			while ((week = teacher->weekMenu()) != teacher->getEndIterator()) {
				system("cls");
				teacher->saveSchedule(week);
				std::cout << "Plan zapisany.\nNacisnij dowolny klawisz aby wrocic" << std::endl;
				_getch();
			}
			break;
		case 3:
			//dodaj zajecia
			while ((week = teacher->weekMenu()) != teacher->getEndIterator()) {
				system("cls");
				addLesson(teacher, week); 
			}
			break;
		case 4:
			//usun zajecia
			while ((week = teacher->weekMenu()) != teacher->getEndIterator()) {
				system("cls");
				deleteLesson(teacher, week);
			}
			break;
		}
	}
}

void Synchronize::addLesson(std::list<GroupSchedule>::iterator group, std::vector<Week>::iterator week) {
	try {
		Lesson lesson = group->getLesson(); //tu gdy sie uda
		int number = week->daysMenu(); //numer dnia, gdzie chcemy wstawic dostajemy 
		std::vector<Day>::iterator day = week->getDay(number); //dostajemy dostep do dnia, do ktorego chcemy dodac 

		try {
			day->addLesson(lesson);

			int classroom = lesson.getClassroom();
			std::string teacherName = lesson.getTeacherName();
			std::string teacherSurname = lesson.getTeacherSurname();
			Date date = week->getStart(); //data poczatkowa tygodnia

			if (!(existClassroom(ClassroomSchedule(startingDate, endingDate, classroom)))) { 
				classrooms.push_back(ClassroomSchedule(startingDate, endingDate, classroom)); //dodanie jesli nie istnieje
				classrooms.sort(ClassroomSchedule::compare); //posortowanie
			}

			std::list<ClassroomSchedule>::iterator classroomSchedule = find(classrooms.begin(), classrooms.end(), ClassroomSchedule(startingDate, endingDate, classroom));
			try {
				classroomSchedule->addLesson(date,number,lesson); //proba dodania do klas lekcji

				if (!(existTeacher(TeacherSchedule(startingDate, endingDate, teacherName,teacherSurname)))) {
					teachers.push_back(TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname)); //dodanie jesli nie istnieje
					teachers.sort(TeacherSchedule::compare); //posortowanie
				}

				std::list<TeacherSchedule>::iterator teacherSchedule = find(teachers.begin(), teachers.end(), TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname));
				try {
					teacherSchedule->addLesson(date, number, lesson);
					std::cout << "Lekcja zostala dodana." << std::endl;
					std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
					_getch();
					return;
				}
				catch (AddingLessonException exc) {
					group->deleteLesson(date, number, lesson);
					classroomSchedule->deleteLesson(date, number, lesson);
					std::cout << "Nie mozna dodac lekcji dla danego nauczyciela." << std::endl;
					if (exc.wrongEndHour) {
						std::cout << "Lekcja konczy sie za pozno." << std::endl;
					}
					if (exc.wrongStartHour) {
						std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
					}
					std::cout << "Sprobuj ponownie." << std::endl;
					std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
					_getch();
					return;
				}

			}
			catch (AddingLessonException exc) {
				//usuniecie dodanej wczesniej
				group->deleteLesson(date, number, lesson);
				std::cout << "Nie mozna dodac lekcji dla danej sali." << std::endl;
				if (exc.wrongEndHour) {
					std::cout << "Lekcja konczy sie za pozno." << std::endl;
				}
				if (exc.wrongStartHour) {
					std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
				}
				std::cout << "Sprobuj ponownie." << std::endl;
				std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
				_getch();
				return;
			}
		}
		catch (AddingLessonException exc) {
			std::cout << "Nie mozna dodac lekcji dla danej grupy." << std::endl;
			if (exc.wrongEndHour) {
				std::cout << "Lekcja konczy sie za pozno." << std::endl;
			}
			if (exc.wrongStartHour) {
				std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
			}
			std::cout << "Sprobuj ponownie." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}


	
	}
	catch (WrongTimeException exc) {
		if (exc.wrongHour) {
			std::cout << "Podano zla godzine." << std::endl;
		}
		if (exc.wrongMinutes) {
			std::cout << "Podano zle minuty." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	catch (WrongLessonException) {
		std::cout << "Godzina koncowa jest mniejsza od/równa poczatkowej." << std::endl << "Sprobuj ponownie." << std::endl <<
			"Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
}

void Synchronize::addLesson(std::list<ClassroomSchedule>::iterator classroom, std::vector<Week>::iterator week) {
	try {
		Lesson lesson = classroom->getLesson(); //tu gdy sie uda
		int number = week->daysMenu(); //numer dnia, gdzie chcemy wstawic dostajemy 
		std::vector<Day>::iterator day = week->getDay(number); //dostajemy dostep do dnia, do ktorego chcemy dodac 

		try {
			day->addLesson(lesson);

			int groupNumber = lesson.getGroupNumber();
			int groupSemester = lesson.getGroupSemester();
			std::string groupSpecialization = lesson.getGroupSpecialization();
			std::string teacherName = lesson.getTeacherName();
			std::string teacherSurname = lesson.getTeacherSurname();
			Date date = week->getStart(); //data poczatkowa tygodnia

			if (!(existGroup(GroupSchedule(startingDate, endingDate, groupNumber,groupSemester,groupSpecialization)))) {
				groups.push_back(GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization)); //dodanie jesli nie istnieje
				groups.sort(GroupSchedule::compare); //posortowanie
			}

			std::list<GroupSchedule>::iterator groupSchedule = find(groups.begin(), groups.end(), GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization));
			try {
				groupSchedule->addLesson(date, number, lesson); //proba dodania do klas lekcji

				if (!(existTeacher(TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname)))) {
					teachers.push_back(TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname)); //dodanie jesli nie istnieje
					teachers.sort(TeacherSchedule::compare); //posortowanie
				}

				std::list<TeacherSchedule>::iterator teacherSchedule = find(teachers.begin(), teachers.end(), TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname));
				try {
					teacherSchedule->addLesson(date, number, lesson);
					std::cout << "Lekcja zostala dodana." << std::endl;
					std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
					_getch();
					return;
				}
				catch (AddingLessonException exc) {
					classroom->deleteLesson(date, number, lesson);
					groupSchedule->deleteLesson(date, number, lesson);
					std::cout << "Nie mozna dodac lekcji dla danego nauczyciela." << std::endl;
					if (exc.wrongEndHour) {
						std::cout << "Lekcja konczy sie za pozno." << std::endl;
					}
					if (exc.wrongStartHour) {
						std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
					}
					std::cout << "Sprobuj ponownie." << std::endl;
					std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
					_getch();
					return;
				}

			}
			catch (AddingLessonException exc) {
				classroom->deleteLesson(date, number, lesson);
				std::cout << "Nie mozna dodac lekcji dla danej grupy." << std::endl;
				if (exc.wrongEndHour) {
					std::cout << "Lekcja konczy sie za pozno." << std::endl;
				}
				if (exc.wrongStartHour) {
					std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
				}
				std::cout << "Sprobuj ponownie." << std::endl;
				std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
				_getch();
				return;
			}
		}
		catch (AddingLessonException exc) {
			std::cout << "Nie mozna dodac lekcji dla danej sali." << std::endl;
			if (exc.wrongEndHour) {
				std::cout << "Lekcja konczy sie za pozno." << std::endl;
			}
			if (exc.wrongStartHour) {
				std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
			}
			std::cout << "Sprobuj ponownie." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}



	}
	catch (WrongTimeException exc) {
		if (exc.wrongHour) {
			std::cout << "Podano zla godzine." << std::endl;
		}
		if (exc.wrongMinutes) {
			std::cout << "Podano zle minuty." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	catch (WrongLessonException) {
		std::cout << "Godzina koncowa jest mniejsza od/równa poczatkowej." << std::endl << "Sprobuj ponownie." << std::endl <<
			"Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
}

void Synchronize::addLesson(std::list<TeacherSchedule>::iterator teacher, std::vector<Week>::iterator week) {
	try {
		Lesson lesson = teacher->getLesson(); //tu gdy sie uda
		int number = week->daysMenu(); //numer dnia, gdzie chcemy wstawic dostajemy 
		std::vector<Day>::iterator day = week->getDay(number); //dostajemy dostep do dnia, do ktorego chcemy dodac 

		try {
			day->addLesson(lesson);

			int groupNumber = lesson.getGroupNumber();
			int groupSemester = lesson.getGroupSemester();
			std::string groupSpecialization = lesson.getGroupSpecialization();
			int classroom = lesson.getClassroom();
			Date date = week->getStart(); //data poczatkowa tygodnia

			if (!(existGroup(GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization)))) {
				groups.push_back(GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization)); //dodanie jesli nie istnieje
				groups.sort(GroupSchedule::compare); //posortowanie
			}

			std::list<GroupSchedule>::iterator groupSchedule = find(groups.begin(), groups.end(), GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization));
			try {
				groupSchedule->addLesson(date, number, lesson); //proba dodania do klas lekcji

				if (!(existClassroom(ClassroomSchedule(startingDate, endingDate, classroom)))) {
					classrooms.push_back(ClassroomSchedule(startingDate, endingDate, classroom)); //dodanie jesli nie istnieje
					classrooms.sort(ClassroomSchedule::compare); //posortowanie
				}

				std::list<ClassroomSchedule>::iterator classroomSchedule = find(classrooms.begin(), classrooms.end(), ClassroomSchedule(startingDate, endingDate, classroom));
				try {
					classroomSchedule->addLesson(date, number, lesson);
					std::cout << "Lekcja zostala dodana." << std::endl;
					std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
					_getch();
					return;
				}
				catch (AddingLessonException exc) {
					teacher->deleteLesson(date, number, lesson);
					classroomSchedule->deleteLesson(date, number, lesson);
					std::cout << "Nie mozna dodac lekcji dla danej sali." << std::endl;
					if (exc.wrongEndHour) {
						std::cout << "Lekcja konczy sie za pozno." << std::endl;
					}
					if (exc.wrongStartHour) {
						std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
					}
					std::cout << "Sprobuj ponownie." << std::endl;
					std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
					_getch();
					return;
				}

			}
			catch (AddingLessonException exc) {
				teacher->deleteLesson(date, number, lesson);
				std::cout << "Nie mozna dodac lekcji dla danej grupy." << std::endl;
				if (exc.wrongEndHour) {
					std::cout << "Lekcja konczy sie za pozno." << std::endl;
				}
				if (exc.wrongStartHour) {
					std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
				}
				std::cout << "Sprobuj ponownie." << std::endl;
				std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
				_getch();
				return;
			}
		}
		catch (AddingLessonException exc) {
			std::cout << "Nie mozna dodac lekcji dla danego nauczyciela." << std::endl;
			if (exc.wrongEndHour) {
				std::cout << "Lekcja konczy sie za pozno." << std::endl;
			}
			if (exc.wrongStartHour) {
				std::cout << "Lekcja zaczyna sie za wczesnie." << std::endl;
			}
			std::cout << "Sprobuj ponownie." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}



	}
	catch (WrongTimeException exc) {
		if (exc.wrongHour) {
			std::cout << "Podano zla godzine." << std::endl;
		}
		if (exc.wrongMinutes) {
			std::cout << "Podano zle minuty." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	catch (WrongLessonException) {
		std::cout << "Godzina koncowa jest mniejsza od/równa poczatkowej." << std::endl << "Sprobuj ponownie." << std::endl <<
			"Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
}

void Synchronize::deleteLesson(std::list<GroupSchedule>::iterator group, std::vector<Week>::iterator week) {
	try {
		Lesson lesson = group->getLesson(); //tu gdy sie uda
		int number = week->daysMenu(); //numer dnia
		std::vector<Day>::iterator day = week->getDay(number); //dostajemy dostep do dnia, do ktorego chcemy dodac 
		try {
			day->deleteLesson(lesson); //proba usuniecia lekcji
			//teraz musimy usunac z classroom i teacher, zakladamy, ze istnieja i ze mozemy usunac, bo przy dodawaniu zawsze dla wszystkich dodajemy
			int classroom = lesson.getClassroom();
			std::string teacherName = lesson.getTeacherName();
			std::string teacherSurname = lesson.getTeacherSurname();
			Date date = week->getStart(); //data poczatkowa tygodnia

			std::list<ClassroomSchedule>::iterator classroomSchedule = find(classrooms.begin(), classrooms.end(), ClassroomSchedule(startingDate, endingDate, classroom));
			classroomSchedule->deleteLesson(date,number,lesson);

			std::list<TeacherSchedule>::iterator teacherSchedule = find(teachers.begin(), teachers.end(), TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname));
			teacherSchedule->deleteLesson(date, number, lesson);
			std::cout << "Lekcja zostala usunieta." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}
		catch (SearchingLessonException) {
			std::cout << "Nie ma takiej lekcji do usuniecia." << std::endl;
			std::cout << "Sprobuj ponownie." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}
	}
	catch (WrongTimeException exc) {
		if (exc.wrongHour) {
			std::cout << "Podano zla godzine." << std::endl;
		}
		if (exc.wrongMinutes) {
			std::cout << "Podano zle minuty." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	catch (WrongLessonException) {
		std::cout << "Godzina koncowa jest mniejsza od/równa poczatkowej." << std::endl << "Sprobuj ponownie." << std::endl <<
			"Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
}

void Synchronize::deleteLesson(std::list<ClassroomSchedule>::iterator classroom, std::vector<Week>::iterator week) {
	try {
		Lesson lesson = classroom->getLesson(); //tu gdy sie uda
		int number = week->daysMenu(); //numer dnia
		std::vector<Day>::iterator day = week->getDay(number); //dostajemy dostep do dnia, do ktorego chcemy dodac 
		try {
			day->deleteLesson(lesson); //proba usuniecia lekcji
			//teraz musimy usunac z group i teacher, zakladamy, ze istnieja i ze mozemy usunac, bo przy dodawaniu zawsze dla wszystkich dodajemy
			
			int groupNumber = lesson.getGroupNumber();
			int groupSemester = lesson.getGroupSemester();
			std::string groupSpecialization = lesson.getGroupSpecialization();
			std::string teacherName = lesson.getTeacherName();
			std::string teacherSurname = lesson.getTeacherSurname();
			Date date = week->getStart(); //data poczatkowa tygodnia

			std::list<GroupSchedule>::iterator groupSchedule = find(groups.begin(), groups.end(), GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization));
			groupSchedule->deleteLesson(date, number, lesson);

			std::list<TeacherSchedule>::iterator teacherSchedule = find(teachers.begin(), teachers.end(), TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname));
			teacherSchedule->deleteLesson(date, number, lesson);

			std::cout << "Lekcja zostala usunieta." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}
		catch (SearchingLessonException) {
			std::cout << "Nie ma takiej lekcji do usuniecia." << std::endl;
			std::cout << "Sprobuj ponownie." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}
	}
	catch (WrongTimeException exc) {
		if (exc.wrongHour) {
			std::cout << "Podano zla godzine." << std::endl;
		}
		if (exc.wrongMinutes) {
			std::cout << "Podano zle minuty." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	catch (WrongLessonException) {
		std::cout << "Godzina koncowa jest mniejsza od/równa poczatkowej." << std::endl << "Sprobuj ponownie." << std::endl <<
			"Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
}

void Synchronize::deleteLesson(std::list<TeacherSchedule>::iterator teacher, std::vector<Week>::iterator week) {
	try {
		Lesson lesson = teacher->getLesson(); //tu gdy sie uda
		int number = week->daysMenu(); //numer dnia
		std::vector<Day>::iterator day = week->getDay(number); //dostajemy dostep do dnia, do ktorego chcemy dodac 
		try {
			day->deleteLesson(lesson); //proba usuniecia lekcji
			//teraz musimy usunac z group i teacher, zakladamy, ze istnieja i ze mozemy usunac, bo przy dodawaniu zawsze dla wszystkich dodajemy

			int groupNumber = lesson.getGroupNumber();
			int groupSemester = lesson.getGroupSemester();
			std::string groupSpecialization = lesson.getGroupSpecialization();
			int classroom = lesson.getClassroom();
			Date date = week->getStart(); //data poczatkowa tygodnia

			std::list<GroupSchedule>::iterator groupSchedule = find(groups.begin(), groups.end(), GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization));
			groupSchedule->deleteLesson(date, number, lesson);

			std::list<ClassroomSchedule>::iterator classroomSchedule = find(classrooms.begin(), classrooms.end(), ClassroomSchedule(startingDate, endingDate, classroom));
			classroomSchedule->deleteLesson(date, number, lesson);

			std::cout << "Lekcja zostala usunieta." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}
		catch (SearchingLessonException) {
			std::cout << "Nie ma takiej lekcji do usuniecia." << std::endl;
			std::cout << "Sprobuj ponownie." << std::endl;
			std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
			_getch();
			return;
		}
	}
	catch (WrongTimeException exc) {
		if (exc.wrongHour) {
			std::cout << "Podano zla godzine." << std::endl;
		}
		if (exc.wrongMinutes) {
			std::cout << "Podano zle minuty." << std::endl;
		}
		std::cout << "Sprobuj ponownie." << std::endl;
		std::cout << "Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
	catch (WrongLessonException) {
		std::cout << "Godzina koncowa jest mniejsza od/równa poczatkowej." << std::endl << "Sprobuj ponownie." << std::endl <<
			"Wcisnij dowolny przycisk by wrocic." << std::endl;
		_getch();
		return;
	}
}

bool Synchronize::operator==(Synchronize s) {
	if (academicYear == s.academicYear) {
		if (semester == s.semester) {
			return true;
		}
	}
	return false;
}

void Synchronize::addLesson(Date date, Lesson lesson) {
	int classroom = lesson.getClassroom();
	if (!(existClassroom(ClassroomSchedule(startingDate, endingDate, classroom)))) {
		classrooms.push_back(ClassroomSchedule(startingDate, endingDate, classroom)); //dodanie jesli nie istnieje
		classrooms.sort(ClassroomSchedule::compare); //posortowanie
	}

	std::list<ClassroomSchedule>::iterator iter_classroom = find(classrooms.begin(), classrooms.end(), ClassroomSchedule(startingDate, endingDate, classroom));
	
	int groupNumber = lesson.getGroupNumber();
	int groupSemester = lesson.getGroupSemester();
	std::string groupSpecialization = lesson.getGroupSpecialization();

	if (!(existGroup(GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization)))) {
		groups.push_back(GroupSchedule(startingDate, endingDate, groupNumber, groupSemester, groupSpecialization)); //dodanie jesli nie istnieje
		groups.sort(GroupSchedule::compare); //posortowanie
	}
	
	std::list<GroupSchedule>::iterator iter_group = find(groups.begin(), groups.end(), GroupSchedule(startingDate, endingDate, groupNumber,groupSemester,groupSpecialization));

	std::string teacherName = lesson.getTeacherName();
	std::string teacherSurname = lesson.getTeacherSurname();
	if (!(existTeacher(TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname)))) {
		teachers.push_back(TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname)); //dodanie jesli nie istnieje
		teachers.sort(TeacherSchedule::compare); //posortowanie
	}

	std::list<TeacherSchedule>::iterator iter_teacher = find(teachers.begin(), teachers.end(), TeacherSchedule(startingDate, endingDate, teacherName, teacherSurname));

	iter_classroom->addLesson(date, lesson);
	iter_group->addLesson(date, lesson); 
	iter_teacher->addLesson(date, lesson);
}
