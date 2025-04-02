#include <iostream>
#include "ExamSchedule.h"
#include "Admin.h"
#include "Student.h"
#include "Course.h"
#include "Acceptance.h"
#include "AllergyInfo.h"
#include "ParentGuardian.h"
#include "Timetable.h"

using namespace std;

void displayMainMenu();
void handleStudentInfo(Student&, Acceptance&, AllergyInfo&, ParentGuardian&);

int main() {
    ExamSchedule es;  
    admin user;
    ExamSchedule examSchedule;
    Student student;
    Course course;
    Acceptance acceptance;
    AllergyInfo allergyInfo;
    ParentGuardian parentGuardian;

    user.login();  // Admin login

    int mainChoice;
    do {
        displayMainMenu();
        if (!(cin >> mainChoice)) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(); // Clear newline left in buffer

        switch (mainChoice) {
        case 1: handleStudentInfo(student, acceptance, allergyInfo, parentGuardian); break;
        case 2: course.displayAvailableCourses();
                course.displayCourseMenu();
                break;
        case 3: es.handleExamMenu(); break;
        case 4: cout << "Exiting system...\n"; break;
        default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (mainChoice != 4);

    return 0;
}
