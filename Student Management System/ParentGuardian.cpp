#include "ParentGuardian.h"
#include <iostream>
#include <fstream>

void ParentGuardian::displayParentInfo() {
    std::ifstream file("parentguardian.txt");
    if (!file) {
        std::cout << "No parent/guardian information available.\n";
        return;
    }

    std::string line;
    std::cout << "\n--- Parent/Guardian Information ---\n";
    while (getline(file, line)) {
        std::cout << line << "\n";
    }

    file.close();
}

void ParentGuardian::addParentInfo() {
    std::ifstream studentFile("student.txt");
    if (!studentFile) {
        std::cout << "Error: Unable to open student.txt\n";
        return;
    }

    std::map<std::string, std::string> studentMap;
    std::string line;
    while (getline(studentFile, line)) {
        std::istringstream iss(line);
        std::string id, name, grade;
        if (getline(iss, id, ',') && getline(iss, name, ',') && getline(iss, grade)) {
            studentMap[id] = name;
        }
    }
    studentFile.close();

    std::string studentID, parentName, contact;
    std::cout << "Enter Student ID: ";
    std::cin >> studentID;
    std::cin.ignore();

    if (studentMap.find(studentID) == studentMap.end()) {
        std::cout << "Student ID not found!\n";
        return;
    }

    std::cout << "Enter Parent/Guardian Name: ";
    getline(std::cin, parentName);
    std::cout << "Enter Contact Info: ";
    getline(std::cin, contact);

    std::ofstream parentFile("parentguardian.txt", std::ios::app);
    parentFile << studentID << ", " << studentMap[studentID] << ", Parent name: " << parentName << ", " << contact << "\n";
    parentFile.close();

    std::cout << "Parent/Guardian information updated successfully!\n";
}
