#include "Header.h"

auto main() -> int {
    bool flag = true;
    Password password("Fuck");
//
//    cout << password.getName() << endl;

//    string password = Password::generatePassword();
//    cout << password << std::endl;
    while (flag) {
        cout
                << "Choose what to do \nEnter 1 if you want to search passwords\nEnter 2 if you want to sort passwords\nEnter 3 if you want to add password\nEnter 4 if you want to edit password\nEnter 5 if you want to delete password\nEnter 6 if you want to add category\nEnter 7 if you want to delete category\n";
        auto ch = -1;
        cin >> ch;


        switch (ch) {
            case 3:
                Password::createPassword();
                break;
            case 0:
                flag = false;
                break;
            default:
                cout << "Wrong input\n";
        }
    }

    return 0;
}