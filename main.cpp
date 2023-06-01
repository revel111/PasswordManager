#include "Header.h"

auto main() -> int {
    Manager::start();
    bool flag = true;
    while (flag) {
        cout
                << "Choose what to do\nEnter 1 if you want to find passwords\nEnter 2 if you want to sort passwords\nEnter 3 if you want to add password\nEnter 4 if you want to edit password\nEnter 5 if you want to delete password\nEnter 6 if you want to add category\nEnter 7 if you want to delete category\nEnter 8 if you want to print all passwords\nEnter 9 if you want to print all categories\nEnter 0 if you want to exit\n";
        auto ch = -1;
        cin >> ch;
        cin.ignore();

        switch (ch) {
            case 1:
                Manager::findRecord();
                break;
            case 2:
                Manager::sortData();
                break;
            case 3:
                Record::addRecord();
                break;
            case 4:
                Manager::editRecord();
                break;
            case 5:
                Manager::deleteRecord();
                break;
            case 6:
                Manager::addCategory();
                break;
            case 7:
                Manager::deleteCategory();
                break;
            case 8:
                Manager::printData();
                break;
            case 9:
                Manager::printCategories();
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