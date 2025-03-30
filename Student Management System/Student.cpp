#include "Student.h"

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
