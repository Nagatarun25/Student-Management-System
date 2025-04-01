#ifndef GRADE_H
#define GRADE_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Grade {
private:
    string studentID;
    string filename;
    map<string, int> studentGrades;
    vector<string> enrolledCourses;

    void loadGrades();
    void saveGrades();
    bool isEnrolled(const string& courseCode);
public:
    Grade(const string& id, const vector<string>& courses);
    void displayGrades();
    void modifyGrades();
    void displayGradesMenu();
    void removeGrade();
};

#endif // GRADES_H