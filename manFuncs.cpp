#include "Header.h"

map<string, vector<Record>> Manager::data;
string Manager::path;

map<string, vector<Record>> Manager::getData() {
    return data;
}

void Manager::insertInData(const string &cat, const Record &record) {
    auto iter = data.find(cat);
    if (iter == data.end()) {
        vector<Record> newVect;
        newVect.push_back(record);
        data.insert({cat, newVect});
    } else
        iter->second.push_back(record);
}

void Manager::printCategories() {
    cout << "List of all categories:\n";
    for (const auto &i: data) {
        const string &cat = i.first;
        cout << cat << '\n';
    }
    cout << '\n';
}

void Manager::printData() {
    cout << "List of all passwords:\n";
    for (const auto &pair: data) {
        cout << "Category: " << pair.first << ";\nPasswords: \n";
        for (auto i = 0; i < pair.second.size(); i++) {
            pair.second.at(i).toString();
            if (i != pair.second.size() - 1)
                cout << '\n';
        }
        cout << '\n';
    }
    cout << '\n';
}

void Manager::addCategory() {
    cout << "Enter name of new category\n";
    string name;
    getline(cin, name);

    if (!Manager::data.contains(name)) {
        data.insert(std::make_pair(name, vector<Record>()));
        Manager::writeInFile();
    } else {
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

void Manager::deleteCategory() {
    printCategories();
    cout << "Enter name of category to delete\n";
    string name;
    getline(cin, name);
    if (Manager::data.contains(name)) {
        data.erase(name);
        Manager::writeInFile();
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
    printData();
    cout << "Enter name of password to delete\n";
    string name;
    getline(cin, name);
    bool flag = false;
    for (auto &pair: data)
        for (int i = 0; i < pair.second.size(); i++)
            if (pair.second.at(i).getName() == name) {
                pair.second.erase(pair.second.begin() + i);
                flag = true;
                break;
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
    Manager::writeInFile();
}

void Manager::checkPassword() {
    string password;
    cout << "Enter the password\n";
    getline(cin, password); //passMan is the password
    bool flag = true;
    string checkStr = "6'55\u000B'(";

    if (checkStr.size() != password.size())
        flag = false;

    for (int i = 0; i < password.size(); i++) {
        checkStr[i] = checkStr[i] ^ 'F';
        if (checkStr[i] != password[i])
            flag = false;
    }

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
    std::ofstream file(path);

    for (const auto &pair: data) {
        string category;
        for (const char &ch: pair.first)
            category += ch ^ 'F';

        if (pair.second.empty())
            file << category << '\n';
        for (const Record &record: pair.second) {
            string name;
            string text;
            string service;
            string login;

            Record encRec = record;

            for (char &ch: encRec.getName())
                name += ch ^ 'F';
            for (char &ch: encRec.getText())
                text += ch ^ 'F';
            for (char &ch: encRec.getService())
                service += ch ^ 'F';
            for (char &ch: encRec.getLogin())
                login += ch ^ 'F';

            file << category << " " << name
                 << " " << text
                 << " " << service
                 << " " << login << '\n';
        }
    }
    file.close();
}

void Manager::readFile() {
    std::ifstream file(path, std::ios::in);

    if (!file.is_open()) {
        cout
                << "You provided wrong path\nEnter 1 if you want to enter program again\nEnter another digit if you do not want to quit\n";
        auto ch = -1;
        cin >> ch;
        cin.ignore();
        if (ch == 1)
            start();
        else
            exit(0);
        return;
    }
    string line;
    while (getline(file, line)) {
        vector<string> values;

        std::istringstream iss(line);
        string value;
        while (iss >> value)
            values.push_back(value);

        if (values.size() == 5) {
            string category = values[0];
            string name = values[1];
            string text = values[2];
            string service = values[3];
            string login = values[4];

            for (char &ch: category)
                ch ^= 'F';
            for (char &ch: name)
                ch ^= 'F';
            for (char &ch: text)
                ch ^= 'F';
            for (char &ch: service)
                ch ^= 'F';
            for (char &ch: login)
                ch ^= 'F';

            Record record(name, text, service, login);
            Manager::insertInData(category, record);
        } else {
            for (char &ch: value)
                ch ^= 'F';
            data.insert(std::make_pair(value, vector<Record>()));
        }
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
            for (auto &pair: data)
                std::sort(pair.second.begin(), pair.second.end(), Record::compareStringsName);
            break;
        case 2:
            for (auto &pair: data)
                std::sort(pair.second.begin(), pair.second.end(), Record::compareStringsText);
            break;
        case 3:
            for (auto &pair: data)
                std::sort(pair.second.begin(), pair.second.end(), Record::compareStringsService);
            break;
        case 4:
            for (auto &pair: data)
                std::sort(pair.second.begin(), pair.second.end(), Record::compareStringsLogin);
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
    Manager::writeInFile();
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
                for (const auto &pair: data)
                    if (pair.first == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        for (auto i = 0; i < pair.second.size(); i++) {
                            pair.second.at(i).toString();
                            if (i != pair.second.size() - 1)
                                cout << '\n';
                        }
                        cout << '\n';
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
            for (auto &pair: data)
                for (int i = 0; i < pair.second.size(); i++)
                    if (pair.second.at(i).getName() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        pair.second.at(i).toString();
                        flag = true;
                        if (i != pair.second.size() - 1)
                            cout << '\n';
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
            for (auto &pair: data)
                for (int i = 0; i < pair.second.size(); i++)
                    if (pair.second.at(i).getText() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        pair.second.at(i).toString();
                        flag = true;
                        if (i != pair.second.size() - 1)
                            cout << '\n';
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
            for (auto &pair: data)
                for (int i = 0; i < pair.second.size(); i++)
                    if (pair.second.at(i).getService() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        pair.second.at(i).toString();
                        flag = true;
                        if (i != pair.second.size() - 1)
                            cout << '\n';
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
            for (auto &pair: data)
                for (int i = 0; i < pair.second.size(); i++)
                    if (pair.second.at(i).getLogin() == choice) {
                        cout << "Category: " << pair.first << "; Passwords: \n";
                        pair.second.at(i).toString();
                        flag = true;
                        if (i != pair.second.size() - 1)
                            cout << '\n';
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
    string name;
    auto ch = -1;
    Manager::printData();
    cout << "Enter the name of a password to edit\n";
    getline(cin, name);
    for (auto &pair: data)
        for (auto &i: pair.second)
            if (i.getName() == name) {
                cout
                        << "Enter 1 if you want to edit name\nEnter 2 if you want to edit password\nEnter 3 if you want to edit website/service\nEnter 4 if you want to edit login\nEnter 0 if you want to stop editing password\n";
                cin >> ch;
                cin.ignore();
                switch (ch) {
                    case 1:
                        cout << "Enter the new name\n";
                        getline(cin, name);
                        for (auto &pairj: data)
                            for (auto &j: pairj.second)
                                if (j.getName() == name) {
                                    cout
                                            << "Wrong input\nEnter 1 if you want to try to edit password again\nEnter another digit if you want to stop editing password\n";
                                    cin >> ch;
                                    cin.ignore();
                                    if (ch == 1)
                                        Manager::editRecord();
                                    return;
                                }
                        i.setName(name);
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
                Manager::writeInFile();
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

void Manager::start() {
    string pathN;
    cout << "Enter the absolute path to your source file\n";
    getline(cin, pathN);
    path = pathN;

    checkPassword(); //passMan is the password
    cout << '\t';
    for (char i: "Password Manager") {
        cout << ' ' << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    cout << '\n';
    readFile();
}