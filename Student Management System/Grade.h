#ifndef GRADE_H
#define GRADE_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class Grade {
private:
    string studentID;
    string filename;
    map<string, int> studentGrades;

    void loadGrades();
    void saveGrades();

public:
    Grade(const string& id);
    void displayGrades();
    void modifyGrades();
    void displayGradesMenu();
    void removeGrade();
};

#endif // GRADES_H