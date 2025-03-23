#include "ExamSchedule.h"

ExamSchedule::ExamSchedule() {
    loadFromFile();
}

void ExamSchedule::loadFromFile() {
    std::ifstream file("exam_schedule.txt");
    if (!file) {
        std::cerr << "Warning: Could not open exam_schedule.txt. Starting with empty schedule.\n";
        return;
    }

    exams.clear();
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        Exam exam;
        if (iss >> exam.courseCode >> exam.examDate >> exam.examTime) {
            exams.push_back(exam);
        }
    }
    file.close();
}

void ExamSchedule::saveToFile() {
    std::ofstream file("exam_schedule.txt");
    if (!file) {
        std::cerr << "Error: Could not save to exam_schedule.txt\n";
        return;
    }

    for (const auto& exam : exams) {
        file << exam.courseCode << " " << exam.examDate << " " << exam.examTime << "\n";
    }
    file.close();
}

void ExamSchedule::addExam(const std::string& courseCode, const std::string& date, const std::string& time) {
    exams.push_back({ courseCode, date, time });
    saveToFile();
}

void ExamSchedule::removeExam(const std::string& courseCode) {
    for (auto it = exams.begin(); it != exams.end(); ++it) {
        if (it->courseCode == courseCode) {
            exams.erase(it);
            saveToFile();
            return;
        }
    }
    std::cerr << "Error: Exam not found.\n";
}

void ExamSchedule::displayExamsForStudent(const std::string& studentNameOrID) {
    std::ifstream studentFile("students.txt");
    if (!studentFile) {
        std::cerr << "Error: Could not open students.txt\n";
        return;
    }

    std::string line, studentID, studentName, enrolledCourse;
    std::vector<std::string> studentCourses;

    while (getline(studentFile, line)) {
        std::istringstream iss(line);
        iss >> studentID >> studentName;
        while (iss >> enrolledCourse) {
            if (studentID == studentNameOrID || studentName == studentNameOrID) {
                studentCourses.push_back(enrolledCourse);
            }
        }
    }

    studentFile.close();

    if (studentCourses.empty()) {
        std::cout << "No exams found for student: " << studentNameOrID << "\n";
        return;
    }

    std::cout << "Exam Schedule for " << studentNameOrID << ":\n";
    for (const auto& exam : exams) {
        for (const auto& course : studentCourses) {
            if (exam.courseCode == course) {
                std::cout << "Course: " << exam.courseCode << " | Date: " << exam.examDate << " | Time: " << exam.examTime << "\n";
            }
        }
    }
}
