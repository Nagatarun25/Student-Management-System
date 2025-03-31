#include "AllergyInfo.h"
#include <iostream>

using namespace std;

AllergyInfo::AllergyInfo() {
    totalAllergies = 0;
}

void AllergyInfo::addAllergy(const string& allergy) {
    if (totalAllergies < 5) {
        allergyList[totalAllergies] = allergy;
        totalAllergies++;
        cout << "Allergy added successfully.\n";
    }
    else {
        cout << "You can only store up to 5 allergies.\n";
    }
}

void AllergyInfo::showAllergies() const {
    if (totalAllergies == 0) {
        cout << "No allergies have been added.\n";
    }
    else {
        cout << "\nRecorded Allergies:\n";
        for (int i = 0; i < totalAllergies; i++) {
            cout << "- " << allergyList[i] << endl;
        }
    }
}

void runAllergyMenu() {
    AllergyInfo allergy;
    int choice;
    string input;

    do {
        cout << "\n=== Allergy Information Menu ===\n";
        cout << "1. Add an allergy\n";
        cout << "2. Show allergies\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        switch (choice) {
        case 1:
            cout << "Enter allergy: ";
            getline(cin, input);
            allergy.addAllergy(input);
            break;

        case 2:
            allergy.showAllergies();
            break;

        case 3:
            cout << "Exiting allergy info menu.\n";
            break;

        default:
            cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 3);
}