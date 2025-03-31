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







//main.cpp code

//#include "Timetable.h"

//int main() {
  //  runTimetableMenu(); //
   // return 0;
//







