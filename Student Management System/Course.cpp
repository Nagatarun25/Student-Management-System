#include "Course.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
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
        return;  // File might not exist yet
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        stringstream ss(line);
        string studentID;
        vector<string> courses;

        // Read student ID (first part before comma)
        if (!getline(ss, studentID, ',')) continue;

        // Read all course codes
        string courseCode;
        while (getline(ss, courseCode, ',')) {
            if (!courseCode.empty()) {
                courses.push_back(courseCode);
            }
        }

        if (!courses.empty()) {
            studentCourses[studentID] = courses;
        }
    }
    file.close();
}

void Course::saveEnrollmentsToFile() {
    ofstream file(enrollmentFilename);
    if (!file) {
        cerr << "Error: Cannot save to " << enrollmentFilename << endl;
        return;
    }

    for (const auto& entry : studentCourses) {
        file << entry.first;  // Student ID
        for (const auto& courseCode : entry.second) {
            file << "," << courseCode;
        }
        file << "\n";
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

            // Check if course exists
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

            // NEW: Check grade level restriction
            if (!isCourseAllowedForStudent(studentID, courseCode)) {
                cout << "Error: This course is not available for your grade level.\n";
                continue;
            }

            studentCourses[studentID].push_back(courseCode);
            saveEnrollmentsToFile();
            cout << "Course added successfully!\n";
        }
        else if (choice == 2) {
            // ... (keep existing remove course logic) ...
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
bool Course::isCourseAllowedForStudent(const string& studentID, const string& courseCode) {
    // Find the student's grade
    int studentGrade = -1;
    ifstream studentFile("Students.txt");
    string line;
    while (getline(studentFile, line)) {
        stringstream ss(line);
        string id, name;
        int grade;
        getline(ss, id, ',');
        getline(ss, name, ',');
        ss >> grade;

        if (id == studentID) {
            studentGrade = grade;
            break;
        }
    }
    studentFile.close();

    if (studentGrade == -1) {
        cerr << "Error: Student not found\n";
        return false;
    }

    // Get the last character of course code
    char lastChar = courseCode.back();
    int courseGradeLevel;

    if (lastChar == '0') {
        return true; // Course is open to all grades
    }
    else if (isdigit(lastChar)) {
        courseGradeLevel = lastChar - '0';
    }
    else {
        return false; // Invalid course code format
    }

    // Check if student's grade matches course grade level
    // Grade 9 = course codes ending with 1
    // Grade 10 = course codes ending with 2, etc.
    return (studentGrade == 9 && courseGradeLevel == 1) ||
        (studentGrade == 10 && courseGradeLevel == 2) ||
        (studentGrade == 11 && courseGradeLevel == 3) ||
        (studentGrade == 12 && courseGradeLevel == 4);
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
        cout << "4. Access Grades Menu\n";
        cout << "5. Go Back\n";
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
        case 4:
        {
            Grade grades(studentID); // Pass studentID to Grade constructor
            grades.displayGradesMenu(); // Call displayGradesMenu without arguments
            break;
        }
        case 5: cout << "Returning to main menu...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (choice != 5); // Exit when 'Go Back' is selected
}