#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Course
{
private:
    struct CourseInfo
    {
        string courseCode;
        string courseName;
    };

    vector<CourseInfo> availableCourses;
    unordered_map<string, vector<string>> studentCourses; // Student ID -> List of course codes
    const string coursesFilename = "Courses.txt";
    const string enrollmentFilename = "Enrollments.txt";

    void loadCoursesFromFile();
    void loadEnrollmentsFromFile();
    void saveEnrollmentsToFile();

public:
    Course();
    void displayAvailableCourses();
    void manageStudentCourses(const string& studentID);
    void displayStudentCourses(const string& studentID);
    void displayCourseEnrollmentCount();
    void displayCourseMenu();
};

#endif