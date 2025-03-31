#include "Timetable.h"
#include <iomanip>



Timetable::Timetable() {

    classCount = 0;
}


void Timetable::add_class(string subject, string time) {

    if (classCount < 6) {

        subjects[classCount] = subject;
        times[classCount] = time;
        classCount++;


    }
    else {
        cout << "Timetable is full! Cannot add more classes. " << endl;
    }

}


void Timetable::displayTimetable() const {

    cout << "\n+----------------------+----------------------+\n";
    cout << "| " << setw(20) << left << "Subject"
        << "| " << setw(20) << left << "Time" << "|\n";
    cout << "+----------------------+----------------------+\n";

    for (int i = 0; i < classCount; i++) {
        cout << "| " << setw(20) << left << subjects[i]
            << "| " << setw(20) << left << times[i] << "|\n";
    }

    cout << "+----------------------+----------------------+\n";
}

void runTimetableMenu() {
    Timetable myTimetable;
    string studentName, studentID;
    const string filename = "timetable_data.txt";

    if (myTimetable.loadFromFile(filename, studentName, studentID)) {
        cout << "Previous timetable data loaded successfully!\n";
    }
    else {
        cout << "Welcome to the Timetable System\n";
        cout << "Enter student name: ";
        getline(cin, studentName);
        cout << "Enter student ID: ";
        getline(cin, studentID);
    }

    int menuChoice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add a class\n";
        cout << "2. Show timetable\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> menuChoice;
        cin.ignore();

        switch (menuChoice) {
        case 1: {
            string subject, time;
            cout << "Enter subject name: ";
            getline(cin, subject);
            cout << "Enter time (e.g., Mon 9AM): ";
            getline(cin, time);
            myTimetable.add_class(subject, time);

            // Save right after adding Fix
            myTimetable.saveToFile(filename, studentName, studentID);

            break;
        }

        case 2:
            cout << "\nStudent: " << studentName << " | ID: " << studentID << endl;
            myTimetable.displayTimetable();
            break;

        case 3:
            myTimetable.saveToFile(filename, studentName, studentID);
            cout << "Data saved. Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please enter 1, 2, or 3.\n"; //Errr message
        }

    } while (menuChoice != 3);
}


#include <fstream>

void Timetable::saveToFile(const string& filename, const string& studentName, const string& studentID) const {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    outFile << studentName << '\n' << studentID << '\n' << classCount << '\n';
    for (int i = 0; i < classCount; ++i) {
        outFile << subjects[i] << '\n' << times[i] << '\n';
    }
    outFile.close();
}

bool Timetable::loadFromFile(const string& filename, string& studentName, string& studentID) {
    ifstream inFile(filename);
    if (!inFile) {
        return false; // No file to load
    }

    getline(inFile, studentName);
    getline(inFile, studentID);
    inFile >> classCount;
    inFile.ignore();

    for (int i = 0; i < classCount; ++i) {
        getline(inFile, subjects[i]);
        getline(inFile, times[i]);
    }

    inFile.close();
    return true;
}




//main.cpp code

//#include "Timetable.h"

//int main() {
  //  runTimetableMenu(); //
   // return 0;
//







