#include "Student.h"
Student::Student(string studentName)
{
    name = studentName;
}

// Getter for name
string Student::getName() const
{
    return name;
}

