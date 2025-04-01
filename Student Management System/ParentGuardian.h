#ifndef PARENTGUARDIAN_H
#define PARENTGUARDIAN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class ParentGuardian {
private:
    struct ParentInfo {
        int studentID;
        string parentName;
        string relationship;
        string contactNumber;
    };
    vector<ParentInfo> parents;
    string filename = "parentguardian.txt";

    void loadFromFile();
    void saveToFile();

public:
    ParentGuardian();
    void addParent();
    void removeParent();
    void displayParents();
    void displayStudentInfo();
};

#endif
