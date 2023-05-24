#include "Header.h"

map<string, vector<Record>> Manager::data;

map<string, vector<Record>> Manager::getData() {
    return map<string, vector<Record>>();
}

void Manager::insertInData(const string &key, const Record &record) {
    auto it = data.find(key);
    if (it == data.end()) {
        std::vector<Record> newVector;
        newVector.push_back(record);
        data.insert({key, newVector});
    } else
        it->second.push_back(record);
}

void Manager::printCategories() {
    cout << "List of all categories\n";
    for (const auto &i: data) {
        const string &key = i.first;
        cout << key << '\n';
    }
}

void Manager::printData() {
    cout << "List of all passwords\n";

    for (const auto &pair: data) {
        cout << "Category: " << pair.first << "; Passwords: \n";
        const vector<Record> &vec = pair.second;
        for (auto i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i != vec.size() - 1)
                cout << '\n';
        }
        cout << '\n';
    }
}

void Manager::addCategory() {
    cout << "Enter name of new category\n";
    string name;
    getline(cin, name);

    if (Manager::data.find(name) == data.end())
        data.insert(std::make_pair(name, vector<Record>()));
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

    auto it = data.find(name);
    if (it != data.end()) {
        data.erase(name);
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