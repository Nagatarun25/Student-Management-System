#include <iostream>
#include "ExamSchedule.h"
#include "Admin.h"
#include "Student.h"

using namespace std;

void displayMainMenu() {
    cout << "\n--- Student Management System ---\n";
    cout << "1. Student Info\n";
    cout << "2. Courses\n";
    cout << "3. Exam Schedule\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void displayStudentMenu() {
    cout << "\n--- Student Info ---\n";
    cout << "1. Display current students\n";
    cout << "2. Graduating students\n";
    cout << "3. Timetable of a student\n";
    cout << "4. Add or remove students\n";
    cout << "5. Allergy Info\n";
    cout << "6. Parent/Guardian Info\n";
    cout << "7. Go Back\n";
    cout << "Enter your choice: ";
}

int main() {
    admin user;
    ExamSchedule examSchedule;
    Student student;

    int mainChoice, studentChoice;
    user.login();  // Admin login

    do {
        displayMainMenu();

        if (!(cin >> mainChoice)) {
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (mainChoice) {
        case 1: // Student Info Section
            do {
                displayStudentMenu();
                if (!(cin >> studentChoice)) {
                    cout << "Invalid input. Please enter a valid number.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }

                switch (studentChoice) {
                case 1:
                    student.displayCurrentStudents();
                    break;
                case 2:
                    student.displayGraduatingStudents();
                    break;
                case 3:
                    student.displayTimetable();
                    break;
                case 4:
                    student.modifyStudents();
                    break;
                case 5:
                    student.displayAllergyInfo();
                    break;
                case 6:
                    student.displayParentInfo();
                    break;
                case 7:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice, try again.\n";
                    break;
                }
            } while (studentChoice != 7);
            break;

        case 2: // Courses Section
            cout << "Course management is not yet implemented.\n";
            break;

        case 3: { // Exam Schedule Section
            int examChoice;
            do {
                cout << "\n--- Exam Schedule Management ---\n";
                cout << "1. Add Exam\n";
                cout << "2. Remove Exam\n";
                cout << "3. Display Exams for Student\n";
                cout << "4. Go Back\n";
                cout << "Enter your choice: ";

                if (!(cin >> examChoice)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }

                switch (examChoice) {
                case 1: {
                    string courseCode, date, time;
                    cout << "Enter Course Code: ";
                    cin >> ws; getline(cin, courseCode);
                    cout << "Enter Exam Date (YYYY-MM-DD): ";
                    cin >> ws; getline(cin, date);
                    cout << "Enter Exam Time (HH:MM): ";
                    cin >> ws; getline(cin, time);

                    examSchedule.addExam(courseCode, date, time);
                    cout << "Exam added successfully!\n";
                    break;
                }
                case 2: {
                    string courseCode;
                    cout << "Enter Course Code to remove: ";
                    cin >> ws; getline(cin, courseCode);

                    examSchedule.removeExam(courseCode);
                    cout << "Exam removed if it existed.\n";
                    break;
                }
                case 3: {
                    string studentIDorName;
                    cout << "Enter Student ID or Name: ";
                    cin >> ws; getline(cin, studentIDorName);

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
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
            break;
        }
    } while (mainChoice != 4);

    return 0;
}

