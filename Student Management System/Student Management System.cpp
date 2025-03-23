#include <iostream>
#include "ExamSchedule.h"

void displayExamMenu() {
    std::cout << "\n--- Exam Schedule Management ---\n";
    std::cout << "1. Add Exam\n";
    std::cout << "2. Remove Exam\n";
    std::cout << "3. Display Exams for Student\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    ExamSchedule examSchedule;
    int choice;

    do {
        displayExamMenu();
        std::cin >> choice;
        std::cin.ignore();  // Ignore newline characters after input

        switch (choice) {
        case 1: {
            std::string courseCode, date, time;
            std::cout << "Enter Course Code: ";
            std::cin >> courseCode;
            std::cout << "Enter Exam Date (YYYY-MM-DD): ";
            std::cin >> date;
            std::cout << "Enter Exam Time (HH:MM): ";
            std::cin >> time;
            examSchedule.addExam(courseCode, date, time);
            std::cout << "Exam added successfully!\n";
            break;
        }
        case 2: {
            std::string courseCode;
            std::cout << "Enter Course Code to remove: ";
            std::cin >> courseCode;
            examSchedule.removeExam(courseCode);
            std::cout << "Exam removed if it existed.\n";
            break;
        }
        case 3: {
            std::string studentIDorName;
            std::cout << "Enter Student ID or Name: ";
            std::cin >> studentIDorName;
            examSchedule.displayExamsForStudent(studentIDorName);
            break;
        }
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
