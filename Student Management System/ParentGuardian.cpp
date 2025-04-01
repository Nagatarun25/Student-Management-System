#include "ParentGuardian.h"

ParentGuardian::ParentGuardian() {
    loadFromFile();
}

void ParentGuardian::loadFromFile() {
    parents.clear();
    ifstream file(filename);
    if (!file) return;

    ParentInfo p;
    while (file >> p.studentID) {
        file.ignore();
        getline(file, p.parentName, ',');
        getline(file, p.relationship, ',');
        getline(file, p.contactNumber);
        parents.push_back(p);
    }
    file.close();
}

void ParentGuardian::saveToFile() {
    ofstream file(filename);
    for (const auto& p : parents) {
        file << p.studentID << "," << p.parentName << "," << p.relationship << "," << p.contactNumber << "\n";
    }
    file.close();
}

void ParentGuardian::displayStudentInfo() {
    ifstream file("student.txt");
    if (!file) {
        cout << "Error opening student.txt!" << endl;
        return;
    }

    cout << "\nStudent List:\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void ParentGuardian::addParent() {
    ParentInfo p;
    cout << "Enter Student ID: ";
    cin >> p.studentID;
    cin.ignore();

    cout << "Enter Parent Name: ";
    getline(cin, p.parentName);

    cout << "Enter Relationship (Mother/Father/Guardian): ";
    getline(cin, p.relationship);

    cout << "Enter Contact Number: ";
    getline(cin, p.contactNumber);

    parents.push_back(p);
    saveToFile();
    cout << "\nParent information added successfully!\n";
}

void ParentGuardian::removeParent() {
    int id;
    string parentName;
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Parent Name to remove: ";
    getline(cin, parentName);

    auto it = remove_if(parents.begin(), parents.end(), [&](const ParentInfo& p) {
        return p.studentID == id && p.parentName == parentName;
    });

    if (it != parents.end()) {
        parents.erase(it, parents.end());
        saveToFile();
        cout << "Parent information removed.\n";
    } else {
        cout << "\nParent not found.\n";
    }
}

void ParentGuardian::displayParents() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();
    cout << endl;
    bool found = false;
    for (const auto& p : parents) {
        if (p.studentID == id) {
            cout << "Parent: " << p.parentName << " (" << p.relationship << ") - " << p.contactNumber << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo parent information found for this student.\n";
    }
}

void runParentGuardian() {
    ParentGuardian pg;
    int choice;
    do {
        cout << "\n1. Display Students\n2. Add Parent Info\n3. Remove Parent Info\n4. Display Parent Info\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                pg.displayStudentInfo();
                break;
            case 2:
                pg.addParent();
                break;
            case 3:
                pg.removeParent();
                break;
            case 4:
                pg.displayParents();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}