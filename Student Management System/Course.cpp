#include "Course.h"
#include <iostream>
Course::Course() {
    loadCoursesFromFile();
    loadEnrollmentsFromFile();
}

void Course::loadCoursesFromFile() {
    availableCourses.clear();
    ifstream file(coursesFilename);
    if (!file) {
        cout << "Error opening file: " << coursesFilename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        CourseInfo course;
        getline(ss, course.courseCode, ',');
        getline(ss, course.courseName);
        availableCourses.push_back(course);
    }

    file.close();
}

void Course::loadEnrollmentsFromFile() {
    studentCourses.clear();
    ifstream file(enrollmentFilename);
    if (!file) {
        // File might not exist yet, that's okay
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string studentID, courseCode;
        getline(ss, studentID, ',');
        vector<string> courses;
        while (getline(ss, courseCode, ',')) {
            if (!courseCode.empty()) {
                courses.push_back(courseCode);
            }
        }
        studentCourses[studentID] = courses;
    }

    file.close();
}

void Course::saveEnrollmentsToFile() {
    ofstream file(enrollmentFilename);
    if (!file) {
        cout << "Error opening file for writing: " << enrollmentFilename << endl;
        return;
    }

    for (const auto& entry : studentCourses) {
        file << entry.first; // Student ID
        for (const auto& course : entry.second) {
            file << "," << course;
        }
        file << endl;
    }

    file.close();
}

void Course::displayAvailableCourses() {
    cout << "\n--- Available Courses ---\n";
    cout << "------------------------------------------\n";
    cout << "Code     | Course Name\n";
    cout << "------------------------------------------\n";
    for (const auto& course : availableCourses) {
        cout << course.courseCode << " | " << course.courseName << endl;
    }
    cout << "------------------------------------------\n";
}

void Course::manageStudentCourses(const string& studentID) {
    int choice;
    do {
        cout << "\n1. Add Course\n2. Remove Course\n3. Go Back\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            if (studentCourses[studentID].size() >= 4) {
                cout << "Error: Maximum of 4 courses per semester.\n";
                continue;
            }

            displayAvailableCourses();
            string courseCode;
            cout << "Enter Course Code to Add: ";
            getline(cin, courseCode);

            bool found = false;
            for (const auto& course : availableCourses) {
                if (course.courseCode == courseCode) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Error: Course not found.\n";
                continue;
            }

            // Check if already enrolled
            if (find(studentCourses[studentID].begin(), studentCourses[studentID].end(), courseCode) != studentCourses[studentID].end()) {
                cout << "Error: Student is already enrolled in this course.\n";
                continue;
            }

            studentCourses[studentID].push_back(courseCode);
            saveEnrollmentsToFile();
            cout << "Course added successfully!\n";
        }
        else if (choice == 2) {
            if (studentCourses[studentID].empty()) {
                cout << "No courses to remove.\n";
                continue;
            }

            cout << "Current enrollments:\n";
            for (const auto& code : studentCourses[studentID]) {
                cout << "- " << code << endl;
            }

            string courseCode;
            cout << "Enter Course Code to Remove: ";
            getline(cin, courseCode);

            auto& courses = studentCourses[studentID];
            auto it = find(courses.begin(), courses.end(), courseCode);
            if (it != courses.end()) {
                courses.erase(it);
                saveEnrollmentsToFile();
                cout << "Course removed successfully!\n";
            }
            else {
                cout << "Error: Course not found in student's enrollment.\n";
            }
        }
    } while (choice != 3);
}

void Course::displayStudentCourses(const string& studentID) {
    cout << "\n--- Enrolled Courses for Student " << studentID << " ---\n";
    if (studentCourses.find(studentID) == studentCourses.end() || studentCourses[studentID].empty()) {
        cout << "No courses enrolled.\n";
    }
    else {
        for (const auto& courseCode : studentCourses[studentID]) {
            // Find course name
            for (const auto& course : availableCourses) {
                if (course.courseCode == courseCode) {
                    cout << courseCode << " - " << course.courseName << endl;
                    break;
                }
            }
        }
    }
}

void Course::displayCourseEnrollmentCount() {
    unordered_map<string, int> courseCount;

    // Initialize all counts to 0
    for (const auto& course : availableCourses) {
        courseCount[course.courseCode] = 0;
    }

    // Count enrollments
    for (const auto& entry : studentCourses) {
        for (const auto& courseCode : entry.second) {
            courseCount[courseCode]++;
        }
    }

    cout << "\n--- Course Enrollment Count ---\n";
    cout << "Code     | Course Name          | Enrolled\n";
    cout << "------------------------------------------\n";
    for (const auto& course : availableCourses) {
        cout << course.courseCode << " | " << left << setw(20) << course.courseName
            << " | " << courseCount[course.courseCode] << endl;
    }
}

void Course::displayCourseMenu() {
    int choice;
    string studentID;

    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();

    do {
        cout << "\n--- Course Management ---\n";
        cout << "1. Add/Remove Courses\n";
        cout << "2. Display Student's Courses\n";
        cout << "3. Display Course Enrollment Counts\n";
        cout << "4. Go Back\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(); // Clear newline left in buffer

        switch (choice) {
        case 1: manageStudentCourses(studentID); break;
        case 2: displayStudentCourses(studentID); break;
        case 3: displayCourseEnrollmentCount(); break;
        case 4: cout << "Returning to main menu...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (choice != 4);
}