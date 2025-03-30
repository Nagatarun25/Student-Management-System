#pragma once
#include <iostream>
#include <string>

using namespace std;

class Timetable {

private:

	string subjects[6];
	string times[6];
	int classCount;




public:

	Timetable(); //default contructor


	//mutators

	void add_class(string subject, string time);


	void displayTimetable() const; //virutal function


};

void runTimetableMenu(); //not apart of object, helper fxn therefore declared outside class