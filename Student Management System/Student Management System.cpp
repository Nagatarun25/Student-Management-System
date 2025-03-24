#include <iostream>
#include "ExamSchedule.h"
#include "Admin.h"
using namespace std;

void displayExamMenu() {
    cout << "\n--- Exam Schedule Management ---\n";
    cout << "1. Add Exam\n";
    cout << "2. Remove Exam\n";
    cout << "3. Display Exams for Student\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    admin user;
    ExamSchedule examSchedule;
    int choice;
    user.login();
    do {
        displayExamMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            cin.clear();  // Clear error flag
            cin.ignore(10000, '\n');  // Ignore incorrect input
            continue;  // Restart the loop
        }
        cin.ignore();

        switch (choice) {
        case 1: {
            string courseCode, date, time;
            cout << "Enter Course Code: ";
            cin >> courseCode;
            cout << "Enter Exam Date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter Exam Time (HH:MM): ";
            cin >> time;
            examSchedule.addExam(courseCode, date, time);
            cout << "Exam added successfully!\n";
            break;
        }
        case 2: {
            string courseCode;
            cout << "Enter Course Code to remove: ";
            cin >> courseCode;
            examSchedule.removeExam(courseCode);
            cout << "Exam removed if it existed.\n";
            break;
        }
        case 3: {
            string studentIDorName;
            cout << "Enter Student ID or Name: ";
            cin >> studentIDorName;
            examSchedule.displayExamsForStudent(studentIDorName);
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}
