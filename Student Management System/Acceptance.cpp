#include "Acceptance.h"
#include <iostream>
#include <fstream>

void Acceptance::displayGraduatingStudents() {
    std::ifstream file("student.txt");
    if (!file) {
        std::cout << "Error: Unable to open student.txt\n";
        return;
    }

    std::string line;
    std::cout << "\n--- Graduating Students ---\n";

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, grade;
        if (getline(iss, id, ',') && getline(iss, name, ',') && getline(iss, grade)) {
            if (grade == "12") {
                std::cout << id << " - " << name << " (Grade " << grade << ")\n";
            }
        }
    }

    file.close();
}
