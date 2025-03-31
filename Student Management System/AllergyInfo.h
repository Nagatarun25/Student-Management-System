#ifndef ALLERGYINFO_H
#define ALLERGYINFO_H

#include <string>

class AllergyInfo {
private:
    std::string allergyList[5];
    int totalAllergies;

public:
    AllergyInfo(); // constructor

    void addAllergy(const std::string& allergy);
    void showAllergies() const;
};

// Menu function for user interaction
void runAllergyMenu();

#endif // ALLERGYINFO_H




//main testing

// #include "AllergyInfo.h"

// int main() {
//    runAllergyMenu();
//   return 0;
//}