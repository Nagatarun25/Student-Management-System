
#include "Admin.h"
#include <iostream>

using namespace std;

admin::admin() {
    password = "password123";
}

void displayMainMenu() {// display menu (after admin login)
    cout << "\n=== Student Management System ===\n";
    cout << "1. Student Info\n";
    cout << "2. Courses\n";
    cout << "3. Exam Schedule\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

bool admin::login()
{
    string inputUsername, inputPassword;

    while (true)
    {
        cout << "Enter Admin Username: ";
        cin >> inputUsername;
        cout << "Enter Password: ";
        cin >> inputPassword;

        if (inputUsername.size() >= 4 && inputUsername.substr(inputUsername.size() - 4) == "@mac")
        {
            if (inputPassword == password)
            {
                cout << "Login successful!\n";
                return true;
            }
            else
            {
                cout << "Incorrect password! Try again.\n";
            }
        }
        else {
            cout << "Invalid username! It must end with '@mac'.\n";
        }
    }
}


