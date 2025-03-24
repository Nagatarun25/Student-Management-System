#include "Course.h"
#include <iostream>
// Hardcoded list of available courses
const std::string Course::availableCourses[TOTAL_COURSES] = {
    "Mathematics",
    "Physics",
    "Chemistry",
    "History",
    "Computer Science"
};

// Constructor (calls base class constructor)
Course::Course(std::string studentName) : Student(studentName) {}

// Function to enroll in a course by index
bool Course::enrollInCourse(int courseIndex) {
    if (courseIndex >= 0 && courseIndex < TOTAL_COURSES && enrolledCourses.size() < MAX_COURSES) {
        enrolledCourses.push_back(availableCourses[courseIndex]);
        return true;
    }
    cout << "Invalid selection or maximum courses reached!\n";
    return false;
}

// Display student name and enrolled courses
void Course::displayCourses() {
    cout << "Student: " << getName() << " is enrolled in:\n";
    if (enrolledCourses.empty()) {
        cout << "  No courses enrolled.\n";
    }
    else {
        for (const auto& course : enrolledCourses) {
            cout << "  - " << course << "\n";
        }
    }
}

// Display all available courses
void Course::displayAvailableCourses() {
    cout << "Available Courses:\n";
    for (int i = 0; i < TOTAL_COURSES; i++) {
        cout << i << ": " << availableCourses[i] << std::endl;
    }
}
