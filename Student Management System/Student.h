#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;
class Student
{
private:
	string name;

public:
	Student(string n);
	string getName() const;
};
#endif
