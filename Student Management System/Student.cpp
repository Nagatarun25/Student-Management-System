#include "Student.h"

Student::Student() {
    students = { "Alice Johnson", "Bob Smith", "Charlie Davis" };
}

void Student::displayCurrentStudents() {
    cout << "\n--- Current Students ---\n";
    for (const auto& student : students) {
        cout << student << endl;
    }
}

void Student::displayGraduatingStudents() {
    cout << "\n--- Graduating Students ---\n";
    cout << "Alice Johnson\n";
}

void Student::displayTimetable() {
    cout << "\n--- Student Timetable ---\n";
    cout << "Monday: Math, Physics\nTuesday: Chemistry, English\n";
}

void Student::modifyStudents() {
    int choice;
    string name;
    cout << "\n1. Add Student\n2. Remove Student\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter student name: ";
        getline(cin, name);
        students.push_back(name);
        cout << name << " added successfully!\n";
    }
    else if (choice == 2) {
        cout << "Enter student name to remove: ";
        getline(cin, name);
        auto it = find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
            cout << name << " removed.\n";
        }
        else {
            cout << "Student not found.\n";
        }
    }
}

void Student::displayAllergyInfo() {
    cout << "\n--- Allergy Information ---\n";
    cout << "Bob Smith - Peanuts Allergy\n";
}

void Student::displayParentInfo() {
    cout << "\n--- Parent/Guardian Information ---\n";
    cout << "Alice Johnson - Guardian: Mr. Johnson\n";
}

