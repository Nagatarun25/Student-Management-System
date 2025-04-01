#ifndef ALLERGYINFO_H
#define ALLERGYINFO_H

#include <iostream>
#include <fstream>
#include <string>

class AllergyInfo {
public:
    AllergyInfo();
    void addAllergy(const std::string& studentID, const std::string& allergy);
    void displayAllergies() const;
    void displayStudentAllergy(const std::string& studentID) const;
    void handleAllergyInfo(); // Function to manage allergy menu
    void removeAllergy(const std::string& studentID, const std::string& allergy);

private:
    const std::string filename = "allergyinfo.txt";
};

#endif

