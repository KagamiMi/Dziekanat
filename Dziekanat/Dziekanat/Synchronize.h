#pragma once
#include "ClassroomSchedule.h"
#include "GroupSchedule.h"
#include "TeacherSchedule.h"
#include <list>
#include "WrongScheduleException.h"
#include <conio.h>
#include <algorithm>
class Synchronize
{
	std::list<ClassroomSchedule> classrooms;
	std::list<GroupSchedule> groups;
	std::list<TeacherSchedule> teachers;
	Date startingDate; 
	Date endingDate;
	std::string semester;
	std::string academicYear;
public:
	Synchronize(Date startingDate, Date endingDate, std::string semester, std::string academicYear);
	~Synchronize();
	void information(); //wypisywanie informacji o planie
	friend std::ostream &operator<<(std::ostream &s, const Synchronize &synchronize);
	void saveDataFile(std::fstream &dataFile);
	static bool compare(Synchronize s1, Synchronize s2);
	void selectChoice();
	int selectMenu();
	std::list<GroupSchedule>::iterator selectGroup();
	std::list<ClassroomSchedule>::iterator selectClassroom();
	std::list<TeacherSchedule>::iterator selectTeacher();
	int groupMenu();
	int classroomMenu();
	int teacherMenu();
	void groupOption();
	void classroomOption();
	void teacherOption();
	void addGroup();
	void addClassroom();
	void addTeacher();
	bool existGroup(GroupSchedule group);
	bool existClassroom(ClassroomSchedule classroom);
	bool existTeacher(TeacherSchedule teacher);
	void selectScheduleChoice(std::list<GroupSchedule>::iterator group);
	void selectScheduleChoice(std::list<ClassroomSchedule>::iterator classroom);
	void selectScheduleChoice(std::list<TeacherSchedule>::iterator teacher);
	void addLesson(std::list<GroupSchedule>::iterator group, std::vector<Week>::iterator week);
	void addLesson(std::list<ClassroomSchedule>::iterator classroom, std::vector<Week>::iterator week);
	void addLesson(std::list<TeacherSchedule>::iterator teacher, std::vector<Week>::iterator week);
	void deleteLesson(std::list<GroupSchedule>::iterator group, std::vector<Week>::iterator week);
	void deleteLesson(std::list<ClassroomSchedule>::iterator classroom, std::vector<Week>::iterator week);
	void deleteLesson(std::list<TeacherSchedule>::iterator teacher, std::vector<Week>::iterator week);
	bool operator==(Synchronize s);
	void addLesson(Date date, Lesson lesson);
};

