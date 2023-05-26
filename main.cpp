#include "Header.h"

using namespace std;

auto main() -> int {
//    Manager::printInitials("Password Manager");
//    bool flag = true;
//    string path;
    string password;
    cout << "Enter the password\n";
    getline(cin, password);

//    cout << "Enter the absolute path to your source file\n";
//    getline(cin, path);
//    Manager::setPath(path);


//    while (flag) {
//        cout
//                << "Choose what to do \nEnter 1 if you want to search passwords\nEnter 2 if you want to sort passwords\nEnter 3 if you want to add password\nEnter 4 if you want to edit password\nEnter 5 if you want to delete password\nEnter 6 if you want to add category\nEnter 7 if you want to delete category\n";
//        auto ch = -1;
//        cin >> ch;
//          cin.ignore();
//
//
//        switch (ch) {
//            case 1:
//                //
//                break;
//            case 2:
//                //
//                break;
//            case 3:
//                Record::createPassword();
//                break;
//            case 4:
//                //
//                break;
//            case 5:
//                //
//                break;
//            case 6:
//                //
//                break;
//            case 7:
//                //
//                break;
//            case 0:
//                flag = false;
//                break;
//            default:
//                cout << "Wrong input\n";
//        }
//    }

    Record record1("record1", "gggg", "fff", 1);
    Record record2("record2");
    Record record3("record3");
    Record record4("record4");

    Manager::insertInData("fff", record1);
    Manager::insertInData("fff", record2);
    Manager::insertInData("aaa", record2);
    Manager::insertInData("abbbb", record2);
    Manager::insertInData("b", record2);
//    Manager::findRecord();
//    Manager::printCategories();
//    Record::addRecord();
//    Manager::addCategory();
//    Manager::deleteRecord();
//    Manager::deleteCategory();
//    Manager::editRecord();
    Manager::checkPassword("passMan");
    Manager::printData();

    return 0;
}