#include "AllergyInfo.h"
#include <iostream>
#include <fstream>

void AllergyInfo::displayAllergyInfo() {
    std::ifstream file("allergyinfo.txt");
    if (!file) {
        std::cout << "No allergy information available.\n";
        return;
    }

    std::string line;
    std::cout << "\n--- Student Allergy Info ---\n";
    while (getline(file, line)) {
        std::cout << line << "\n";
    }

    file.close();
}

void AllergyInfo::addAllergy() {
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

    std::string studentID, allergy;
    std::cout << "Enter Student ID: ";
    std::cin >> studentID;
    std::cin.ignore();

    if (studentMap.find(studentID) == studentMap.end()) {
        std::cout << "Student ID not found!\n";
        return;
    }

    std::cout << "Enter Allergy Information: ";
    getline(std::cin, allergy);

    std::ofstream allergyFile("allergyinfo.txt", std::ios::app);
    allergyFile << studentID << ", " << studentMap[studentID] << ", " << allergy << "\n";
    allergyFile.close();

    std::cout << "Allergy information updated successfully!\n";
}
