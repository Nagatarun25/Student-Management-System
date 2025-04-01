#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Timetable {
private:
    string studentID;
    vector<string> subjects;
    vector<string> times;
    vector<string> roomNumbers;

public:
    Timetable();

    bool loadTimetable(const string& filename, const string& studentID);
    void saveTimetable(const string& filename) const;

    void addCourse(const string& course, const string& time, const string& room);
    bool removeCourse(const string& course);
    void displayTimetable() const;
};

void runTimetableMenu();
