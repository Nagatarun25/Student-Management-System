#include <iostream>
#include "Student.h"
#include "Acceptance.h"
#include "AllergyInfo.h"
#include "ParentGuardian.h"
#include "Timetable.h"

void displayStudentMenu();
void runTimetableMenu();
void runParentGuardian();

Student::Student() {
    loadStudentsFromFile();
}

void Student::loadStudentsFromFile() {
    students.clear();
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        StudentInfo student;
        getline(ss, student.id, ',');
        getline(ss, student.name, ',');
        ss >> student.grade;
        students.push_back(student);
    }

    file.close();
}

void Student::saveStudentsToFile() {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& student : students) {
        file << student.id << "," << student.name << "," << student.grade << endl;
    }

    file.close();
}

void Student::displayCurrentStudents() {
    cout << "\n--- Current Students ---\n";
    for (const auto& student : students) {
        cout << "ID: " << student.id << " | Name: " << student.name << " | Grade: " << student.grade << endl;
    }
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
        case 5: allergyInfo.handleAllergyInfo(); break;
        case 6:runParentGuardian(); break;
        case 7: cout << "Returning to main menu...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (studentChoice != 7);
}

void Student::modifyStudents() {
    int choice;
    cout << "\n1. Add Student\n2. Remove Student\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        StudentInfo newStudent;
        cout << "Enter Student ID: ";
        getline(cin, newStudent.id);
        cout << "Enter Student Name: ";
        getline(cin, newStudent.name);
        cout << "Enter Grade: ";
        cin >> newStudent.grade;
        students.push_back(newStudent);
        saveStudentsToFile();
        cout << "Student added successfully!\n";
    }
    else if (choice == 2) {
        string id;
        cout << "Enter Student ID to remove: ";
        getline(cin, id);
        auto it = remove_if(students.begin(), students.end(), [&](const StudentInfo& s) { return s.id == id; });
        if (it != students.end()) {
            students.erase(it, students.end());
            saveStudentsToFile();
            cout << "Student removed successfully!\n";
        }
        else {
            cout << "Student not found.\n";
        }
    }
}
