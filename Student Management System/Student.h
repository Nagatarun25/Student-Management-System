#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Student {
private:
    struct StudentInfo {
        string id;
        string name;
        int grade;
    };
    vector<StudentInfo> students;
    const string filename = "Student.txt";

public:
    Student();
    void loadStudentsFromFile();
    void saveStudentsToFile();
    void displayCurrentStudents();
  /*  void displayGraduatingStudents();
    void displayTimetable();*/
    void modifyStudents();
    //void displayAllergyInfo();
    //void displayParentInfo();
};

#endif
