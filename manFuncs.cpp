#include "Header.h"

map<string, vector<Record>> Manager::data;

map<string, vector<Record>> Manager::getData() {
    return data;
}

//string Manager::getPath() {
//    return path;
//}
//
//void Manager::setPath(string str) {
//    path = std::move(str);
//}

void Manager::insertInData(const string &key, const Record &record) {
    auto it = data.find(key);
    if (it == data.end()) {
        vector<Record> newVector;
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
    string name;
    getline(cin, name);
    bool flag = false;
    for (auto &pair: data) {
        vector<Record> &records = pair.second;
        for (int i = 0; i < records.size(); i++)
            if (records.at(i).getName() == name) {
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

void Manager::checkPassword() {
    string password;
    cout << "Enter the password\n";
    getline(cin, password);
//    char xorKey = 'F';
    std::ifstream file("check.txt");

//    for (int i = 0; i < input.size(); ++i) {
//        input[i] = input[i] ^ xorKey;
//        file << input[i];
//    }
    bool flag = true;
    char check;
    auto counter = 0;
    while (file >> std::noskipws >> check) {
        check = check ^ 'F';
        if (check == password[counter])
            counter++;
        else
            flag = false;
    }
    file.close();

    if (counter > password.size() || counter < password.size())
        flag = false;

    if (!flag) {
        auto ch = 0;
        cout
                << "Wrong input\nEnter 1 if you want to try to enter program again\nEnter another digit if you do not want to enter program\n";
        cin >> ch;
        cin.ignore();
        if (ch == 1)
            Manager::checkPassword();
        return;
    }
}

void Manager::writeInFile() {
    std::ofstream file("test.txt");

    for (const auto &pair: data) {
        file << pair;
    }

    file.close();
}

void Manager::sortData() {
    Manager::printData();
    cout
            << "Enter 1 if you want to sort passwords by category and name\nEnter 2 if you want to sort passwords by category and password\nEnter 3 if you want to sort passwords by category and service/website\nEnter 4 if you want to sort passwords by category and login\nEnter 0 if you want to stop sorting passwords\n";
    auto ch = -1;
    cin >> ch;
    cin.ignore();
    switch (ch) {
        case 1:
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                std::sort(vec.begin(), vec.end(), Record::compareStringsName);
            }
            break;
        case 2:
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                std::sort(vec.begin(), vec.end(), Record::compareStringsText);
            }
            break;
        case 3:
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                std::sort(vec.begin(), vec.end(), Record::compareStringsService);
            }
            break;
        case 4:
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                std::sort(vec.begin(), vec.end(), Record::compareStringsLogin);
            }
            break;
        case 0:
            return;
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to try to sort passwords again\nEnter another digit if you want to stop sorting passwords\n";
            cin >> ch;
            cin.ignore();
            if (ch == 1)
                Manager::sortData();
            return;
    }
}

void Manager::findRecord() {
    cout
            << "Enter 1 if you want to find password by its category\nEnter 2 if you want to find password by its name\nEnter 3 if you want to find password by its text\nEnter 4 if you want to find password by its service\nEnter 5 if you want to find password by its login\nEnter 0 if you want to stop searching for password\n";
    auto ch = -1;
    cin >> ch;
    cin.ignore();
    string choice;
    bool flag = false;
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
                        flag = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!flag) {
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
            cout << "Enter a password\n";
            getline(cin, choice);
            for (auto &pair: data) {
                vector<Record> &vec = pair.second;
                for (int i = 0; i < vec.size(); i++)
                    if (vec.at(i).getText() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        cout << vec[i];
                        flag = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!flag) {
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
                        flag = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!flag) {
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
                        flag = true;
                        if (i != vec.size() - 1)
                            cout << '\n';
                    }
            }
            if (!flag) {
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

void Manager::editRecord() {
    cout << "Enter the name of a password to edit\n";
    string name;
    auto ch = -1;
    Manager::printData();
    getline(cin, name);
    for (auto &pair: data) {
        vector<Record> &vec = pair.second;
        for (auto &i: vec)
            if (i.getName() == name) {
                cout
                        << "Enter 1 if you want to edit name\nEnter 2 if you want to edit password\nEnter 3 if you want to edit website/service\nEnter 4 if you want to edit login\nEnter 0 if you want to stop editing password\n";
                cin >> ch;
                cin.ignore();
                switch (ch) {
                    case 1:
                        cout << "Enter the new name\n";
                        getline(cin, name);
                        i.setName(name);
                        for (auto &pairj: data) {
                            vector<Record> &vecj = pairj.second;
                            for (auto &j: vecj)
                                if (j.getName() == name) {
                                    cout
                                            << "Wrong input\nEnter 1 if you want to try to edit password again\nEnter another digit if you want to stop editing password\n";
                                    cin >> ch;
                                    cin.ignore();
                                    if (ch == 1)
                                        Manager::editRecord();
                                    return;
                                }
                        }
                        break;
                    case 2:
                        cout << "Enter the new password\n";
                        getline(cin, name);
                        i.setText(name);
                        break;
                    case 3:
                        cout << "Enter the new website/service\n";
                        getline(cin, name);
                        i.setService(name);
                        break;
                    case 4:
                        cout << "Enter the new login\n";
                        getline(cin, name);
                        i.setLogin(name);
                        break;
                    default:
                        cout
                                << "Wrong input\nEnter 1 if you want to try to edit password again\nEnter another digit if you want to stop editing password\n";
                        cin >> ch;
                        cin.ignore();
                        if (ch == 1)
                            Manager::editRecord();
                        return;
                }
            } else {
                cout
                        << "Wrong input\nEnter 1 if you want to try to edit password again\nEnter another digit if you want to stop editing password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Manager::editRecord();
                return;
            }
    }
}

void Manager::start(const string &str) {
    system("Color 0A");
    cout << '\t';
    for (char i: str) {
        cout << ' ' << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    cout << '\n';
    system("Color 7");
}