#include "Header.h"

vector<Record> Manager::passwordVector;
vector<string> Manager::categoryVector;
map<string, vector<Record>> Manager::data;


vector<Record> Manager::getPasswordVector() {
    return vector<Record>();
}

vector<string> Manager::getCategoryVector() {
    return vector<string>();
}

map<string, vector<Record>> Manager::getData() {
    return map<string, vector<Record>>();
}

void Manager::printCategories() {
    cout << "List of all categories\n";
    for (const auto &i: data) {
        const string &key = i.first;
        cout << key << '\n';
    }
}

void Manager::addCategory() {
    cout << "Enter name of new category\n";
    string name;
    getline(cin, name);
//    Manager::categoryVector.push_back(name);

    if (Manager::data.find(name) == data.end())
        data.insert(std::make_pair(name, std::vector<Record>()));
    else {
        auto ch = -1;
        cout
                << "Category already exists\nEnter 1 if you want to try to add category again\nEnter another digit if you want to stop adding category\n";
        cin >> ch;
        cin.ignore();
        if (ch == 1)
            Manager::addCategory();
        return;
    }

}

void Manager::deleteCategory() {
    cout << "Enter name of category to delete\n";
    string name;
    getline(cin, name);

    if (std::find(categoryVector.begin(), categoryVector.end(), name) != categoryVector.end()) {
        categoryVector.erase(std::remove(categoryVector.begin(), categoryVector.end(), name), categoryVector.end());

        for (int i = 0; i < passwordVector.size(); i++)
            if (passwordVector.at(i).getName() == name)
                passwordVector.erase(passwordVector.begin() + i);

//        for (auto it = passwordVector.begin(); it != passwordVector.end();)
//            if (it->getName() == name)
//                it = passwordVector.erase(it); // Remove the element and update iterator
//            else
//                ++it; // Move to the next element

    } else {
        auto ch = -1;
        cout
                << "Wrong input\nEnter 1 if you want to try to delete category again\nEnter another digit if you want to stop deleting category\n";
        cin >> ch;
        cin.ignore();
        if (ch == 1)
            Manager::deleteCategory();
        return;
    }
}