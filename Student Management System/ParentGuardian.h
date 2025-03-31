#ifndef PARENTGUARDIAN_H
#define PARENTGUARDIAN_H

#include <string>

class ParentGuardian {
private:
    std::string parentNames[5];
    std::string contactInfo[5];
    int count;

public:
    ParentGuardian(); // constructor

    void addParent(const std::string& name, const std::string& contact);
    void showParents() const;
};

// Menu function for user interaction
void runParentGuardianMenu();

#endif // PARENTGUARDIAN_H




// MAIN CODE 
// #include "ParentGuardian.h"

// int main() {
  //  runParentGuardianMenu();
  //  return 0;
// }
