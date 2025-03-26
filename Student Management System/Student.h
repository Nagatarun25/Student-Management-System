#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
private:
    vector<string> students;
public:
    Student();
    void displayCurrentStudents();
    void displayGraduatingStudents();
    void displayTimetable();
    void modifyStudents();
    void displayAllergyInfo();
    void displayParentInfo();
};

#endif
