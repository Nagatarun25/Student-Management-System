#include "Grade.h"

Grade::Grade(const string& id, const vector<string>& courses)
    : studentID(id), enrolledCourses(courses) {
    filename = "Grad_" + studentID + ".txt";
    loadGrades();
}
bool Grade::isEnrolled(const string& courseCode) {
    return find(enrolledCourses.begin(), enrolledCourses.end(), courseCode) != enrolledCourses.end();
}
void Grade::loadGrades() {
    studentGrades.clear();
    ifstream file(filename);
    if (!file) return;

    string courseCode;
    int grade;
    while (file >> courseCode >> grade) {
        // Only load grades for enrolled courses
        if (isEnrolled(courseCode)) {
            studentGrades[courseCode] = grade;
        }
    }
    file.close();
}

void Grade::saveGrades() {
    ofstream file(filename);
    if (!file) {
        cout << "Error saving grades for " << studentID << endl;
        return;
    }
    for (const auto& entry : studentGrades) {
        file << entry.first << " " << entry.second << endl;
    }
    file.close();
}

void Grade::displayGrades() {
    cout << "\n--- Grades for Student " << studentID << " ---\n";
    if (studentGrades.empty()) {
        cout << "No grades recorded.\n";
        return;
    }
    for (const auto& entry : studentGrades) {
        cout << "Course: " << entry.first << " | Grade: " << entry.second << endl;
    }
}

void Grade::displayGradesMenu() {
    int choice;
    do {
        cout << "\n--- Grades Management for Student " << studentID << " ---\n";
        cout << "1. View Grades\n";
        cout << "2. Add/Update Grade\n";
        cout << "3. Remove Grade\n";
        cout << "4. Go Back\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore();  // Clear newline left in buffer

        switch (choice) {
        case 1:
            displayGrades();
            break;
        case 2:
            modifyGrades();
            break;
        case 3:
            removeGrade();
            break;
        case 4:
            cout << "Returning to previous menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);  // Exit when 'Go Back' is selected
}

void Grade::modifyGrades() {
    string courseCode;
    int grade;

    cout << "Enter Course Code: ";
    cin >> courseCode;

    if (!isEnrolled(courseCode)) {
        cout << "Error: Student is not enrolled in this course.\n";
        return;
    }

    cout << "Enter Grade (0-100): ";
    if (!(cin >> grade) || grade < 0 || grade > 100) {
        cout << "Invalid grade. Please enter a value between 0-100.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    studentGrades[courseCode] = grade;
    saveGrades();
    cout << "Grade updated!\n";
}

void Grade::removeGrade() {
    string courseCode;
    cout << "Enter Course Code to remove: ";
    cin >> courseCode;

    if (!isEnrolled(courseCode)) {
        cout << "Error: Student is not enrolled in this course.\n";
        return;
    }

    if (studentGrades.erase(courseCode)) {
        saveGrades();
        cout << "Grade removed!\n";
    }
    else {
        cout << "No grade found for this course.\n";
    }
}