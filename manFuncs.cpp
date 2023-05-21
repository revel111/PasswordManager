#include "Header.h"

vector<Password> Manager::getPasswordVector() {
    return vector<Password>();
}

vector<string> Manager::getCategoryVector() {
    return vector<string>();
}

void Manager::addCategory() {
    cout << "Enter name of new category\n";
    string name;
    cin >> name;
    categoryVector.push_back(name);
}

//void Manager::deleteCategory() {
//    cout << "Enter name of new category\n";
//    string name;
//    cin >> name;
//    categoryVector.push_back(name);
//
//    remove(categoryVector.begin(), categoryVector.end(), name);
//
////    if()
////
////    else {
////        auto ch = -1;
////        cout
////                << "Wrong input\nEnter 1 if you want to try to delete category again\nEnter another digit if you want to stop deleting category\n";
////        cin >> ch;
////        if (ch == 1)
////            Manager::deleteCategory();
////        return;
////    }
//
//}