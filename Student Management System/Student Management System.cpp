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
void runParentGuardianMenu();



//f
void handleStudentInfo(Student& student, Acceptance& acceptance, AllergyInfo& allergyInfo, ParentGuardian& parentGuardian) {
    int studentChoice;
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
        case 5:
            int allergyChoice;
            cout << "\n1. Display Allergy Info\n2. Add Allergy Info\nEnter choice: ";
            cin >> allergyChoice;
            cin.ignore();
            //if (allergyChoice == 1) allergyInfo.displayAllergyInfo();
            //else if (allergyChoice == 2) allergyInfo.addAllergy();
            //else cout << "Invalid choice.\n";
            break;
        case 6:runParentGuardianMenu(); break;
        case 7: cout << "Returning to main menu...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (studentChoice != 7);
}

void handleExamSchedule(ExamSchedule& examSchedule) {
    int examChoice;
    do {
        cout << "\n--- Exam Schedule Management ---\n";
        cout << "1. Add Exam\n";
        cout << "2. Remove Exam\n";
        cout << "3. Display Exams for Student\n";
        cout << "4. Go Back\n";
        cout << "Enter your choice: ";

        if (!(cin >> examChoice)) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(); // Clear newline left in buffer

        switch (examChoice) {
        case 1: {
            string courseCode, date, time;
            cout << "Enter Course Code: "; getline(cin, courseCode);
            cout << "Enter Exam Date (YYYY-MM-DD): "; getline(cin, date);
            cout << "Enter Exam Time (HH:MM): "; getline(cin, time);
            examSchedule.addExam(courseCode, date, time);
            cout << "Exam added successfully!\n";
            break;
        }
        case 2: {
            string courseCode;
            cout << "Enter Course Code to remove: "; getline(cin, courseCode);
            examSchedule.removeExam(courseCode);
            cout << "Exam removed if it existed.\n";
            break;
        }
        case 3: {
            string studentIDorName;
            cout << "Enter Student ID or Name: "; getline(cin, studentIDorName);
            examSchedule.displayExamsForStudent(studentIDorName);
            break;
        }
        case 4:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
            break;
        }
    } while (examChoice != 4);
}

int main() {
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
        case 3: handleExamSchedule(examSchedule); break;
        case 4: cout << "Exiting system...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (mainChoice != 4);

    return 0;
}
