#include "ParentGuardian.h"
#include <iostream>

using namespace std;

ParentGuardian::ParentGuardian() {
    count = 0;
}

void ParentGuardian::addParent(const string& name, const string& contact) {
    if (count < 5) {
        parentNames[count] = name;
        contactInfo[count] = contact;
        count++;
        cout << "Parent/Guardian added successfully.\n";
    }
    else {
        cout << "Maximum number of entries reached (5).\n";
    }
}

void ParentGuardian::showParents() const {
    if (count == 0) {
        cout << "No parent/guardian information available.\n";
    }
    else {
        cout << "\nParent/Guardian Information:\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << parentNames[i] << " | Contact: " << contactInfo[i] << endl;
        }
    }
}

void runParentGuardianMenu() {
    ParentGuardian pg;
    int choice;
    string name, contact;

    do {
        cout << "\n=== Parent/Guardian Menu ===\n";
        cout << "1. Add parent/guardian info\n";
        cout << "2. Show parent/guardian info\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        switch (choice) {
        case 1:
            cout << "Enter parent/guardian name: ";
            getline(cin, name);
            cout << "Enter contact info: ";
            getline(cin, contact);
            pg.addParent(name, contact);
            break;

        case 2:
            pg.showParents();
            break;

        case 3:
            cout << "Exiting parent/guardian menu.\n";
            break;

        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 3);
}