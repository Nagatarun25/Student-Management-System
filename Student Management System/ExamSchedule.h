#ifndef EXAMSCHEDULE_H
#define EXAMSCHEDULE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Structure to hold exam information for each student
struct ExamInfo {
    int studentID;
    string studentName;
    string subject;
    string date;
    string time;
};

class ExamSchedule {
private:
    vector<ExamInfo> exams;  // Vector to store exam information
    const string filename = "exam_schedule.txt";  // File name for saving exam schedules
    vector<pair<string, string>> courses;  // List of courses with their names
    vector<pair<int, vector<string>>> enrolledCourses;  // Enrolled courses for each student

public:
    ExamSchedule();  // Constructor to load existing exam data
    void loadCourses();  // Load course data from courses.txt
    void loadEnrolledCourses();  // Load enrolled courses data from EnrolledCourses.txt
    void loadFromFile();  // Load exam data from examSchedule.txt
    void saveToFile();  // Save exam data to examSchedule.txt

    void addExam();  // Add a new exam entry
    void removeExam();  // Remove an exam entry
    void displayExams();  // Display all scheduled exams
    void displayStudentExams();  // Display exams for a specific student
    void generateExamSchedule();  // Generate exam schedule based on enrolled courses

    void handleExamMenu();  // Display the exam menu and handle user interaction
};

#endif
