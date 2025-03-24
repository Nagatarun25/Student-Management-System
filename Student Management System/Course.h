#ifndef COURSE_H
#define COURSE_H

#include "Student.h"
#include <vector>

const int MAX_COURSES = 5; // Maximum courses a student can take

class Course : public Student {
private:
    std::vector<std::string> enrolledCourses; // Stores the enrolled courses

public:
    static const int TOTAL_COURSES = 5; // Number of available courses
    static const std::string availableCourses[TOTAL_COURSES]; // Hardcoded courses

    // Constructor
    Course(std::string studentName);

    // Function to enroll in a course by index
    bool enrollInCourse(int courseIndex);

    // Function to display student and enrolled courses
    void displayCourses();

    // Static function to display available courses
    static void displayAvailableCourses();
};

#endif
