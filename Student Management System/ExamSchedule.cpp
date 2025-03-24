#include "ExamSchedule.h"

using namespace std;

ExamSchedule::ExamSchedule() {
    loadFromFile();
}

void ExamSchedule::loadFromFile() {
    ifstream file("exam_schedule.txt");
    if (!file) {
        cerr << "Warning: Could not open exam_schedule.txt. Starting with empty schedule.\n";
        return;
    }

    exams.clear();
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Exam exam;
        if (iss >> exam.courseCode >> exam.examDate >> exam.examTime) {
            exams.push_back(exam);
        }
    }
    file.close();
}

void ExamSchedule::saveToFile() {
    ofstream file("exam_schedule.txt");
    if (!file) {
        cerr << "Error: Could not save to exam_schedule.txt\n";
        return;
    }

    for (const auto& exam : exams) {
        file << exam.courseCode << " " << exam.examDate << " " << exam.examTime << "\n";
    }
    file.close();
}

void ExamSchedule::addExam(const string& courseCode, const string& date, const string& time) {
    exams.push_back({ courseCode, date, time });
    saveToFile();
}

void ExamSchedule::removeExam(const string& courseCode) {
    for (auto it = exams.begin(); it != exams.end(); ++it) {
        if (it->courseCode == courseCode) {
            exams.erase(it);
            saveToFile();
            return;
        }
    }
    cerr << "Error: Exam not found.\n";
}

void ExamSchedule::displayExamsForStudent(const string& studentNameOrID) {
    ifstream studentFile("students.txt");
    if (!studentFile) {
        cerr << "Error: Could not open students.txt\n";
        return;
    }

    string line, studentID, studentName, enrolledCourse;
    vector<string> studentCourses;

    while (getline(studentFile, line)) {
        istringstream iss(line);
        iss >> studentID >> studentName;
        while (iss >> enrolledCourse) {
            if (studentID == studentNameOrID || studentName == studentNameOrID) {
                studentCourses.push_back(enrolledCourse);
            }
        }
    }

    studentFile.close();

    if (studentCourses.empty()) {
        cout << "No exams found for student: " << studentNameOrID << "\n";
        return;
    }

    cout << "Exam Schedule for " << studentNameOrID << ":\n";
    for (const auto& exam : exams) {
        for (const auto& course : studentCourses) {
            if (exam.courseCode == course) {
                cout << "Course: " << exam.courseCode << " | Date: " << exam.examDate << " | Time: " << exam.examTime << "\n";
            }
        }
    }
}
