#ifndef ADMIN_H
#define ADMIN_H
#include <string>
using namespace std;
class Admin
{
private:
    string password;

public:
    admin(); // Constructor to set default credentials
    bool login(); // Function to authenticate user
};

#endif

