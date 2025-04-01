#include <iostream>
#include "ExamSchedule.h"
#include "Admin.h"
#include "Student.h"
#include "Course.h"
#include "Acceptance.h"
#include "AllergyInfo.h"
#include "ParentGuardian.h"
#include "Timetable.h"

using namespace std;

void displayMainMenu() {// display menu (after admin login)
    cout << "\n=== Student Management System ===\n";
    cout << "1. Student Info\n";
    cout << "2. Courses\n";
    cout << "3. Exam Schedule\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void displayStudentMenu() { //student submenu
    cout << "\n--- Student Info ---\n";
    cout << "1. Display Current Students\n";
    cout << "2. Display Graduating Students\n";
    cout << "3. Display Student Timetable\n";
    cout << "4. Add/Remove Students\n";
    cout << "5. Allergy Info\n";
    cout << "6. Parent/Guardian Info\n";
    cout << "7. Go Back\n";
    cout << "Enter your choice: ";
}

void runTimetableMenu();
void runParentGuardian();


//f
void handleStudentInfo(Student& student, Acceptance& acceptance, AllergyInfo& allergyInfo, ParentGuardian& parentGuardian) {
    int studentChoice;
    string studentID;

    do {
        displayStudentMenu();
        if (!(cin >> studentChoice)) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(); // Clear newline left in buffer

        switch (studentChoice) {
        case 1: student.displayCurrentStudents(); break;
        case 2: acceptance.displayGraduatingStudents(); break;
        case 3: runTimetableMenu(); break;
        case 4: student.modifyStudents(); break;
        case 5: allergyInfo.handleAllergyInfo();break;
        case 6:runParentGuardian(); break;
        case 7: cout << "Returning to main menu...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (studentChoice != 7);
}

int main() {
    ExamSchedule es;    // Create an object of ExamSchedule class

    admin user;
    ExamSchedule examSchedule;
    Student student;
    Course course;
    Acceptance acceptance;
    AllergyInfo allergyInfo;
    ParentGuardian parentGuardian;

    user.login();  // Admin login

    int mainChoice;
    do {
        displayMainMenu();
        if (!(cin >> mainChoice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(); // Clear newline left in buffer

        switch (mainChoice) {
        case 1: handleStudentInfo(student, acceptance, allergyInfo, parentGuardian); break;
        case 2: course.displayAvailableCourses();
                course.displayCourseMenu();
                break;
        case 3: es.handleExamMenu(); break;
        case 4: cout << "Exiting system...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (mainChoice != 4);

    return 0;
}
