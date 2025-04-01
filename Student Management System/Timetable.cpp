#include "Timetable.h"

Timetable::Timetable() {}

bool Timetable::loadTimetable(const string& filename, const string& studentID) {
    this->studentID = studentID;
    ifstream inFile(filename);
    if (!inFile) {
        return false;
    }

    string line;
    subjects.clear();
    times.clear();
    roomNumbers.clear();

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, subject, time, room;
        getline(ss, id, ',');

        if (id == studentID) {
            while (getline(ss, subject, ',') &&
                getline(ss, time, ',') &&
                getline(ss, room, ',')) {
                subjects.push_back(subject);
                times.push_back(time);
                roomNumbers.push_back(room);
            }
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

void Timetable::saveTimetable(const string& filename) const {
    ifstream inFile(filename);
    vector<string> fileLines;
    string line;

    while (getline(inFile, line)) {
        if (line.find(studentID + ",") != 0) {
            fileLines.push_back(line);
        }
    }
    inFile.close();

    ofstream outFile(filename);
    for (const string& line : fileLines) {
        outFile << line << "\n";
    }

    outFile << studentID;
    for (size_t i = 0; i < subjects.size(); ++i) {
        outFile << "," << subjects[i] << "," << times[i] << "," << roomNumbers[i];
    }
    outFile << "\n";
    outFile.close();
}

void Timetable::addCourse(const string& course, const string& time, const string& room) {
    subjects.push_back(course);
    times.push_back(time);
    roomNumbers.push_back(room);
}

bool Timetable::removeCourse(const string& course) {
    for (size_t i = 0; i < subjects.size(); ++i) {
        if (subjects[i] == course) {
            subjects.erase(subjects.begin() + i);
            times.erase(times.begin() + i);
            roomNumbers.erase(roomNumbers.begin() + i);
            return true;
        }
    }
    return false;
}

void Timetable::displayTimetable() const {
    cout << "+-----------------------------------------------------+\n";
    cout << "| Student ID: " << studentID << "                                      |\n";
    cout << "+------------+---------------------+-----------------+\n";
    cout << "| Course     | Time                | Room           |\n";
    cout << "+------------+---------------------+-----------------+\n";

    for (size_t i = 0; i < subjects.size(); i++) {
        cout << "| " << setw(10) << left << subjects[i] << " | "
            << setw(21) << left << times[i] << " | "
            << setw(15) << left << roomNumbers[i] << " |\n";
    }

    cout << "+------------+---------------------+-----------------+\n";
}


void runTimetableMenu() {
    string studentID;
    cout << "Enter student ID: ";
    cin >> studentID;
    cin.ignore();

    Timetable myTimetable;
    myTimetable.loadTimetable("timetable_data.txt", studentID);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Course\n";
        cout << "2. Remove Course\n";
        cout << "3. Display Timetable\n";
        cout << "4. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string course, time, room;
            cout << "Enter course code: ";
            getline(cin, course);
            cout << "Enter time (e.g., 9:00 AM - 10:00 AM): ";
            getline(cin, time);
            cout << "Enter room number: ";
            getline(cin, room);
            myTimetable.addCourse(course, time, room);
            break;
        }
        case 2: {
            string course;
            cout << "Enter course code to remove: ";
            getline(cin, course);
            if (myTimetable.removeCourse(course)) {
                cout << "Course removed successfully.\n";
            }
            else {
                cout << "Course not found!\n";
            }
            break;
        }
        case 3:
            myTimetable.displayTimetable();
            break;
        case 4:
            myTimetable.saveTimetable("timetable_data.txt");
            cout << "Timetable saved. Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}
