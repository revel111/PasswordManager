#include "Header.h"

map<string, vector<Record>> Manager::data;

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
    cout << "List of all categories:\n";
    for (const auto &i: data) {
        const string &key = i.first;
        cout << key << '\n';
    }
}

void Manager::printData() {
    cout << "List of all passwords:\n";
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
//Manager::data.find(name) == data.end()
    if (!Manager::data.contains(name))
        data.insert(std::make_pair(name, vector<Record>()));
    else {
        auto ch = -1;
        cout
                << "Wrong input\nEnter 1 if you want to try to add category again\nEnter another digit if you want to stop adding category\n";
        cin >> ch;
        cin.ignore();
        if (ch == 1)
            Manager::addCategory();
        return;
    }
}

string Manager::addCategory(bool f) {
    cout << "Enter name of new category\n";
    string name;
    getline(cin, name);

    if (!Manager::data.contains(name))
        data.insert(std::make_pair(name, vector<Record>()));
    else {
        auto ch = -1;
        cout
                << "Wrong input\nEnter 1 if you want to try to add category again\nEnter another digit if you want to stop adding category\n";
        cin >> ch;
        cin.ignore();
        if (ch == 1)
            Manager::addCategory();
        return "";
    }
    return name;
}

void Manager::deleteCategory() {
    cout << "Enter name of category to delete\n";
    string name;
    getline(cin, name);
    //Manager::data.find(name) != data.end()
    if (Manager::data.contains(name)) {
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

void Manager::deleteRecord() {
    cout << "Enter name of password to delete\n";
    string nameN;
    getline(cin, nameN);
    bool flag = false;
    for (auto &pair: data) {
        vector<Record> &records = pair.second;
        for (int i = 0; i < records.size(); ++i)
            if (records.at(i).getName() == nameN) {
                records.erase(records.begin() + i);
                flag = true;
            }
    }

    if (!flag) {
        auto ch = -1;
        cout
                << "Wrong input\nEnter 1 if you want to try to delete password again\nEnter another digit if you want to stop deleting password\n";
        cin >> ch;
        cin.ignore();
        if (ch == 1)
            Manager::deleteRecord();
        return;
    }
}

bool Manager::checkPassword() {

}

string Manager::writeInFile() {
    std::ofstream file("check.txt");
    std::ostream_iterator<string> output_iterator(file, "\n");


}

void Manager::sortData() {
    Manager::printData();
    cout
            << "Enter 1 if you want to sort passwords by category and name\nEnter 2 if you want to sort passwords by category and password\nEnter 3 if you want to sort passwords by category and service/website\nEnter 4 if you want to sort passwords by category and login\n";
    auto ch = -1;
    cin >> ch;
    cin.ignore();
    switch(ch) {
        case 1:
    }
}

void Manager::findRecord() {
    cout
            << "Enter 1 if you want to find password by its category\nEnter 2 if you want to find password by its name\nEnter 3 if you want to find password by its text\nEnter 4 if you want to find password by its service\nEnter 5 if you want to find password by its login\nEnter 0 if you want to stop searching for password\n";
    auto ch = -1;
    cin >> ch;
    cin.ignore();
    string choice;
    bool f = false;
    switch (ch) {
        case 1:
            cout << "Enter a category\n";
            getline(cin, choice);
            if (Manager::data.contains(choice)) {
                for (const auto &pair: data) {
                    if (pair.first == choice) {
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
            } else {
                cout
                        << "Wrong input\nEnter 1 if you want to try to find password again\nEnter another digit if you want to stop finding password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Manager::findRecord();
                return;
            }
            break;
        case 2:
            cout << "Enter a name\n";
            getline(cin, choice);
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                for (int i = 0; i < vec.size(); i++)
                    if (vec.at(i).getName() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        cout << vec[i];
                        f = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!f) {
                cout
                        << "Wrong input\nEnter 1 if you want to try to find password again\nEnter another digit if you want to stop finding password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Manager::findRecord();
                return;
            }
            break;
        case 3:
            cout << "Enter a text\n";
            getline(cin, choice);
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                for (int i = 0; i < vec.size(); i++)
                    if (vec.at(i).getText() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        cout << vec[i];
                        f = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!f) {
                cout
                        << "Wrong input\nEnter 1 if you want to try to find password again\nEnter another digit if you want to stop finding password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Manager::findRecord();
                return;
            }
            break;
        case 4:
            cout << "Enter a service\n";
            getline(cin, choice);
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                for (int i = 0; i < vec.size(); i++)
                    if (vec.at(i).getService() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        cout << vec[i];
                        f = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!f) {
                cout
                        << "Wrong input\nEnter 1 if you want to try to find password again\nEnter another digit if you want to stop finding password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Manager::findRecord();
                return;
            }
            break;
        case 5:
            cout << "Enter a login\n";
            getline(cin, choice);
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                for (int i = 0; i < vec.size(); i++)
                    if (vec.at(i).getLogin() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        cout << vec[i];
                        f = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!f) {
                cout
                        << "Wrong input\nEnter 1 if you want to try to find password again\nEnter another digit if you want to stop finding password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Manager::findRecord();
                return;
            }
            break;
        case 0:
            return;
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to try to find password again\nEnter another digit if you want to stop finding password\n";
            cin >> ch;
            cin.ignore();
            if (ch == 1)
                Manager::findRecord();
            return;
    }
}

void Manager::printInitials(const string &str) {
    system("Color 0A");
    cout << '\t';
    for (char i: str) {
        cout << ' ' << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    cout << '\n';
    system("Color 7");
}