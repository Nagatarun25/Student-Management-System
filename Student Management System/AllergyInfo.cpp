#include "AllergyInfo.h"

AllergyInfo::AllergyInfo() {
    // Constructor does nothing special
}

void AllergyInfo::addAllergy(const std::string& studentID, const std::string& allergy) {
    std::ofstream file(filename, std::ios::app); // Append mode
    if (!file) {
        std::cout << "Error opening file!\n";
        return;
    }
    file << studentID << "," << allergy << "\n";
    file.close();
    std::cout << "Allergy added for student " << studentID << ".\n";
}

void AllergyInfo::displayAllergies() const {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "No allergy data found.\n";
        return;
    }

    std::string studentIDs[100];   // Array to store student IDs
    std::string allergies[100];    // Array to store allergies in the same index as student IDs
    int count = 0;                 // Number of students recorded

    std::string studentID, allergy;

    // Read from file and store data in arrays
    while (getline(file, studentID, ',') && getline(file, allergy)) {
        bool found = false;

        // Check if student ID already exists in our list
        for (int i = 0; i < count; i++) {
            if (studentIDs[i] == studentID) {
                // Append the allergy to the existing entry
                allergies[i] += ", " + allergy;
                found = true;
                break;
            }
        }

        // If student ID is not found, add a new entry
        if (!found && count < 100) {
            studentIDs[count] = studentID;
            allergies[count] = allergy;
            count++;
        }
    }
    file.close();

    // Display formatted table
    std::cout << "\n=== Student Allergy Information ===\n";
    std::cout << "-----------------------------------\n";
    std::cout << "Student ID  | Allergies\n";
    std::cout << "-----------------------------------\n";

    for (int i = 0; i < count; i++) {
        std::cout << studentIDs[i] << "       | " << allergies[i] << "\n";
    }

    std::cout << "-----------------------------------\n";
}

void AllergyInfo::displayStudentAllergy(const std::string& studentID) const {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "No allergy data found.\n";
        return;
    }

    std::string id, allergy;
    bool found = false;
    while (getline(file, id, ',') && getline(file, allergy)) {
        if (id == studentID) {
            std::cout << "Student ID: " << id << " | Allergy: " << allergy << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No allergy record found for Student ID: " << studentID << ".\n";
    }

    file.close();
}

void AllergyInfo::removeAllergy(const std::string& studentID, const std::string& allergy) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "No allergy data found.\n";
        return;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cout << "Error creating temporary file!\n";
        return;
    }

    std::string id, recordedAllergy;
    bool found = false;

    while (getline(file, id, ',') && getline(file, recordedAllergy)) {
        if (id == studentID) {
            std::string newAllergyList;
            size_t pos = recordedAllergy.find(allergy);

            // Check if allergy exists in the string and remove it
            if (pos != std::string::npos) {
                found = true;
                recordedAllergy.erase(pos, allergy.length());
                // Remove trailing comma if needed
                if (recordedAllergy[pos] == ',') {
                    recordedAllergy.erase(pos, 1);
                }
                // Remove leading comma if needed
                if (!recordedAllergy.empty() && recordedAllergy[0] == ',') {
                    recordedAllergy.erase(0, 1);
                }
            }

            if (!recordedAllergy.empty()) {
                tempFile << id << "," << recordedAllergy << "\n";
            }
        }
        else {
            tempFile << id << "," << recordedAllergy << "\n";
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        std::cout << "Allergy '" << allergy << "' removed for student " << studentID << ".\n";
    }
    else {
        std::cout << "Allergy not found for Student ID: " << studentID << ".\n";
        remove("temp.txt"); // Cleanup
    }
}



void AllergyInfo::handleAllergyInfo() {
    int choice;
    do {
        std::cout << "\n=== Allergy Information Menu ===\n";
        std::cout << "1. Add Allergy\n";
        std::cout << "2. Display All Allergies\n";
        std::cout << "3. Display Student Allergy\n";
        std::cout << "4. Remove Allergy\n";
        std::cout << "5. Go Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear buffer

        switch (choice) {
        case 1: {
            std::string id, allergy;
            std::cout << "Enter Student ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter Allergy: ";
            std::getline(std::cin, allergy);
            addAllergy(id, allergy);
            break;
        }
        case 2:
            displayAllergies();
            break;
        case 3: {
            std::string id;
            std::cout << "Enter Student ID: ";
            std::getline(std::cin, id);
            displayStudentAllergy(id);
            break;
        }
        case 4: {
            std::string id, allergy;
            std::cout << "Enter Student ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter Allergy to Remove: ";
            std::getline(std::cin, allergy);
            removeAllergy(id, allergy);
            break;
        }
        case 5:
            std::cout << "Returning to Student Info Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);
}
