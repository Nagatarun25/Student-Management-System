#include "Timetable.h"
#include <iomanip>



Timetable::Timetable() {

    classCount = 0;
}


void Timetable::add_class(string subject, string time) {

    if (classCount < 6) {

        subjects[classCount] = subject;
        times[classCount] = time;
        classCount++;


    }
    else {
        cout << "Timetable is full! Cannot add more classes. " << endl;
    }

}


void Timetable::displayTimetable() const {

    cout << "\n+----------------------+----------------------+\n";
    cout << "| " << setw(20) << left << "Subject"
        << "| " << setw(20) << left << "Time" << "|\n";
    cout << "+----------------------+----------------------+\n";

    for (int i = 0; i < classCount; i++) {
        cout << "| " << setw(20) << left << subjects[i]
            << "| " << setw(20) << left << times[i] << "|\n";
    }

    cout << "+----------------------+----------------------+\n";
}

void runTimetableMenu() {
    Timetable myTimetable;
    string studentName, studentID;
    int menuChoice;

    cout << "Welcome to the Timetable System\n";

    // Get student info
    cout << "Enter student name: ";
    getline(cin, studentName);
    cout << "Enter student ID: ";
    getline(cin, studentID);

    // Menu loop
    do {
        cout << "\nMenu:\n";
        cout << "1. Add a class\n";
        cout << "2. Show timetable\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> menuChoice;
        cin.ignore(); // clean input buffer

        switch (menuChoice) {
        case 1: {
            string subject, time;
            cout << "Enter subject name: ";
            getline(cin, subject);
            cout << "Enter time (e.g., Mon 9AM): ";
            getline(cin, time);
            myTimetable.add_class(subject, time);
            break;
        }

        case 2:
            cout << "\nStudent: " << studentName << " | ID: " << studentID << endl;
            myTimetable.displayTimetable();
            break;

        case 3:
            cout << "Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please enter 1, 2, or 3.\n"; //Errr message
        }

    } while (menuChoice != 3);
}


























//testtt





















//#include "Student.h"
//
//Student::Student() {
//    students = { "Alice Johnson", "Bob Smith", "Charlie Davis" };
//}
//
//void Student::displayCurrentStudents() {
//    cout << "\n--- Current Students ---\n";
//    for (const auto& student : students) {
//        cout << student << endl;
//    }
//}
//
//void Student::displayGraduatingStudents() {
//    cout << "\n--- Graduating Students ---\n";
//    cout << "Alice Johnson\n";
//}
//
//void Student::displayTimetable() {
//    cout << "\n--- Student Timetable ---\n";
//    cout << "Monday: Math, Physics\nTuesday: Chemistry, English\n";
//}
//
//void Student::modifyStudents() {
//    int choice;
//    string name;
//    cout << "\n1. Add Student\n2. Remove Student\nEnter choice: ";
//    cin >> choice;
//    cin.ignore();
//
//    if (choice == 1) {
//        cout << "Enter student name: ";
//        getline(cin, name);
//        students.push_back(name);
//        cout << name << " added successfully!\n";
//    }
//    else if (choice == 2) {
//        cout << "Enter student name to remove: ";
//        getline(cin, name);
//        auto it = find(students.begin(), students.end(), name);
//        if (it != students.end()) {
//            students.erase(it);
//            cout << name << " removed.\n";
//        }
//        else {
//            cout << "Student not found.\n";
//        }
//    }
//}
//
//void Student::displayAllergyInfo() {
//    cout << "\n--- Allergy Information ---\n";
//    cout << "Bob Smith - Peanuts Allergy\n";
//}
//
//void Student::displayParentInfo() {
//    cout << "\n--- Parent/Guardian Information ---\n";
//    cout << "Alice Johnson - Guardian: Mr. Johnson\n";
//}
