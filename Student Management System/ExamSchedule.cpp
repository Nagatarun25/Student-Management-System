#include "ExamSchedule.h"

// Constructor to load existing exam data
ExamSchedule::ExamSchedule() {
    loadFromFile();
    loadCourses();  // Load course information
    loadEnrolledCourses();  // Load enrolled student information
}

// Load course data from courses.txt (with course code and name)
void ExamSchedule::loadCourses() {
    ifstream courseFile("Courses.txt");
    string courseCode, courseName;

    while (getline(courseFile, courseCode, ',') && getline(courseFile, courseName)) {
        courses.push_back({ courseCode, courseName });  // Store course data
    }
    courseFile.close();
}

// Load enrolled courses data from EnrolledCourses.txt
void ExamSchedule::loadEnrolledCourses() {
    ifstream enrolledFile("EnrolledCourses.txt");
    string line;
    while (getline(enrolledFile, line)) {
        stringstream ss(line);
        int studentID;
        string courseCode;
        vector<string> courseCodes;

        // Parsing the student data
        ss >> studentID;
        getline(ss, courseCode, ',');  // Ignore the student ID part

        // Collect course codes for this student
        while (getline(ss, courseCode, ',')) {
            courseCodes.push_back(courseCode);
        }

        enrolledCourses.push_back({ studentID, courseCodes });
    }
    enrolledFile.close();
}

// Load exam data from examSchedule.txt
void ExamSchedule::loadFromFile() {
    exams.clear();
    ifstream file(filename);
    if (!file) return;

    ExamInfo e;
    while (file >> e.studentID) {
        file.ignore();
        getline(file, e.studentName, ',');
        getline(file, e.subject, ',');
        getline(file, e.date, ',');
        getline(file, e.time);
        exams.push_back(e);
    }
    file.close();
}

// Save exam data to examSchedule.txt
void ExamSchedule::saveToFile() {
    ofstream file(filename);
    for (const auto& e : exams) {
        file << e.studentID << "," << e.studentName << "," << e.subject << "," << e.date << "," << e.time << "\n";
    }
    file.close();
}

// Add a new exam entry
void ExamSchedule::addExam() {
    ExamInfo e;
    cout << "Enter Student ID: ";
    cin >> e.studentID;
    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, e.studentName);

    cout << "Enter Course Code: ";
    getline(cin, e.subject);

    cout << "Enter Exam Date (YYYY-MM-DD): ";
    getline(cin, e.date);

    cout << "Enter Exam Time (HH:MM AM/PM): ";
    getline(cin, e.time);

    exams.push_back(e);
    saveToFile();
    cout << "Exam scheduled successfully!\n";
}

// Remove an exam entry
void ExamSchedule::removeExam() {
    int id;
    string subject;
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Course to remove: ";
    getline(cin, subject);

    // Simple loop to remove the exam
    for (auto it = exams.begin(); it != exams.end(); ++it) {
        if (it->studentID == id && it->subject == subject) {
            exams.erase(it);
            saveToFile();
            cout << "Exam removed successfully.\n";
            return;
        }
    }
    cout << "Exam not found.\n";
}

// Display all exams
void ExamSchedule::displayExams() {
    cout << "\nExam Schedule:\n";
    for (const auto& e : exams) {
        cout << e.studentID << " - " << e.studentName << " | " << e.subject << " | " << e.date << " | " << e.time << "\n";
    }
}

// Display exams for a specific student
void ExamSchedule::displayStudentExams() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();

    cout << "\nExams for Student ID " << id << ":\n";
    bool found = false;
    for (const auto& e : exams) {
        if (e.studentID == id) {
            cout << e.subject << " | " << e.date << " | " << e.time << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No exams scheduled for this student.\n";
    }
}

// Generate exam schedule based on enrolled courses
void ExamSchedule::generateExamSchedule() {
    for (const auto& enrolled : enrolledCourses) {
        int studentID = enrolled.first;
        string studentName = "Student " + to_string(studentID);  // Simplified name for now
        for (const auto& courseCode : enrolled.second) {
            string subject;
            // Find the course name based on the course code
            for (const auto& course : courses) {
                if (course.first == courseCode) {
                    subject = course.second;
                    break;
                }
            }

            // Generate exam info
            string examDate = "2025-06-01";  // Example date
            string examTime = "10:00 AM";    // Example time

            ExamInfo e;
            e.studentID = studentID;
            e.studentName = studentName;
            e.subject = subject;
            e.date = examDate;
            e.time = examTime;

            exams.push_back(e);
        }
    }
    saveToFile();
}

// Handle the exam menu
void ExamSchedule::handleExamMenu() {
    int choice;
    do {
        cout << "\n--- Exam Schedule Menu ---\n";
        cout << "1. Display All Exams\n";
        cout << "2. Add Exam\n";
        cout << "3. Remove Exam\n";
        cout << "4. Display Student Exams\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            displayExams();
            break;
        case 2:
            addExam();
            break;
        case 3:
            removeExam();
            break;
        case 4:
            displayStudentExams();
            break;
        case 5:
            cout << "Exiting Exam Menu...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}
