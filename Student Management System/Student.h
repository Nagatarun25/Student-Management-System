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
    const string filename = "Students.txt";

public:
    Student();
    void loadStudentsFromFile();
    void saveStudentsToFile();
    void displayCurrentStudents();
    void modifyStudents();

};

#endif
