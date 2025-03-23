#ifndef EXAMSCHEDULE_H
#define EXAMSCHEDULE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ExamSchedule {
private:
    struct Exam {
        string courseCode;
        string examDate;
        string examTime;
    };

    vector<Exam> exams;

    void loadFromFile();  // Loads exams from a file
    void saveToFile();    // Saves exams to a file

public:
    ExamSchedule();   // Constructor to load data

    void addExam(const std::string& courseCode, const std::string& date, const std::string& time);
    void removeExam(const std::string& courseCode);
    void displayExamsForStudent(const std::string& studentNameOrID);
};

#endif // EXAMSCHEDULE_H
