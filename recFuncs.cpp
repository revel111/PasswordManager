#include "Header.h"

Record::Record(string name, string text, string service, string login) {
    this->name = std::move(name);
    this->text = std::move(text);
    this->service = std::move(service);
    this->login = std::move(login);
}

string Record::getName() {
    return name;
}

string Record::getText() {
    return text;
}

string Record::getService() {
    return service;
}

string Record::getLogin() {
    return login;
}

void Record::setName(string name) {
    this->name = std::move(name);
}

void Record::setText(string text) {
    this->text = std::move(text);
}

void Record::setService(string service) {
    this->service = std::move(service);
}

void Record::setLogin(string login) {
    this->login = std::move(login);
}

bool Record::compareStringsName(const Record &first, const Record &second) {
    return first.name < second.name;
}

bool Record::compareStringsText(const Record &first, const Record &second) {
    return first.text < second.text;
}

bool Record::compareStringsService(const Record &first, const Record &second) {
    return first.service < second.service;
}

bool Record::compareStringsLogin(const Record &first, const Record &second) {
    return first.login < second.login;
}

void Record::toString() const {
    cout << "Name: " << name << "; Password: " << text << "; Service: " << service << "; Login: " << login
         << ';';
}

void Record::addRecord() {
    auto ch = 0;
    string name;
    string password;
    string category;
    string service;
    string login;

    Manager::printData();
    cout << "Enter the unique name of a password\n";
    getline(cin, name);

    for (auto &pair: Manager::getData())
        for (auto &record: pair.second)
            if (record.getName() == name) {
                cout
                        << "This name already exists\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Record::addRecord();
                return;
            }

    cout
            << "Enter 1 if you want to create your own password\nEnter 2 if you want to generate password\nEnter 0 if you want to want to stop creating password\n";
    cin >> ch;
    cin.ignore();

    switch (ch) {
        case 1:
            cout << "Enter a password. A number of characters should be 5-20\n";
            getline(cin, password);
            if (password.size() < 5 || password.size() > 20) {
                cout
                        << "Wrong input\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Record::addRecord();
                return;
            }
            break;
        case 2 :
            password = Record::generatePassword();
            break;
        case 0:
            return;
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
            cin >> ch;
            cin.ignore();
            if (ch == 1)
                Record::addRecord();
            return;
    }

    if (password.empty())
        return;

    auto score = 0;
    std::set<char> uniqueItems;

    bool arr[4];

    for (bool &i: arr)
        i = false;

    for (char i: password) {
        uniqueItems.insert(i);
        if (isdigit(i) && !arr[0]) {
            score += 15;
            arr[0] = true;
        } else if (std::ispunct(i) && !arr[1]) {
            score += 15;
            arr[1] = true;
        } else if (std::islower(i) && !arr[2]) {
            score += 15;
            arr[2] = true;
        } else if (std::isupper(i) && !arr[3]) {
            score += 15;
            arr[3] = true;
        }
    }

    if (uniqueItems.size() > 5)
        score += 20;
    if (password.size() >= 12)
        score += 20;

    cout << "The strength of your password: " << password << " is " << score
         << "/100 \nEnter 1 if you want to use this password\nEnter another digit if you want to try to create password again\n";
    cin >> ch;
    cin.ignore();
    if (ch != 1) {
        Record::addRecord();
        return;
    }

    cout
            << "Enter 1 if you want to choose existing category\nEnter 2 if you want to create new category\nEnter 0 if you want to stop creating password\n";
    cin >> ch;
    cin.ignore();

    switch (ch) {
        case 1:
            Manager::printCategories();
            cout << "Enter a name of a category\n";
            getline(cin, category);
            if (!Manager::getData().contains(category)) {
                cout
                        << "Category does not exist\nEnter 1 if you want to try to create password again\nEnter another digit if you want to try to create password again\n";
                cin >> ch;
                cin.ignore();
                if (ch == 1)
                    Record::addRecord();
                return;
            }
            break;
        case 2:
            cout << "Enter a name of a category\n";
            getline(cin, category);
            break;
        case 0:
            return;
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
            cin >> ch;
            cin.ignore();
            if (ch == 1)
                Record::addRecord();
            return;
    }

    if (category.empty())
        return;

    cout
            << "Enter 1 if you want to add website/service\nEnter 2 if you do not want to add website/service\nEnter 0 if you want to stop creating password\n";
    cin >> ch;
    cin.ignore();

    switch (ch) {
        case 1:
            cout << "Enter a website/service\n";
            getline(cin, service);
            break;
        case 2:
            service = "no";
            break;
        case 0:
            return;
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
            cin >> ch;
            cin.ignore();
            if (ch == 1)
                Record::addRecord();
            return;
    }

    cout
            << "Enter 1 if you want to add login\nEnter 2 if you do not want to add login\nEnter 0 if you want to stop creating password\n";
    cin >> ch;
    cin.ignore();

    switch (ch) {
        case 1:
            cout << "Enter a login\n";
            getline(cin, login);
            break;
        case 2:
            login = "no";
            break;
        case 0:
            return;
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
            cin >> ch;
            cin.ignore();
            if (ch == 1)
                Record::addRecord();
            return;
    }
    Record record(name, password, service, login);
    Manager::insertInData(category, record);
    Manager::writeInFile();
}

string Record::generatePassword() {
    auto lowCase = "abcdefghijklmnopqrstuvwxyz";
    auto upCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    auto specialChar = "£$&()*+[]@#^-_!?";
    string characters = "0123456789";

    auto numberChar = 0;
    auto specialSymbols = -1;
    auto lowerUpper = -1;

    cout << "Enter number of characters 5-20\n";
    cin >> numberChar;
    cin.ignore();

    if (numberChar < 5 || numberChar > 20) {
        cout
                << "Wrong input\nEnter 1 if you want to generate password again\nEnter another digit if you want to stop creating password\n";
        cin >> numberChar;
        cin.ignore();
        if (numberChar == 1)
            Record::generatePassword();
        return "";
    }

    cout
            << "Enter 1 if you want to have lowercase and uppercase letters\nEnter 2 if you want to have only lowercase letters\nEnter 3 if you want to have only uppercase letters\nEnter 4 if you do not want to have letters\nEnter 0 if you want to want to stop generating password\n";
    cin >> lowerUpper;
    cin.ignore();

    switch (lowerUpper) {
        case 1:
            characters += upCase;
            characters += lowCase;
            break;
        case 2:
            characters += lowCase;
            break;
        case 3:
            characters += upCase;
            break;
        case 4:
            break;
        case 0:
            return "";
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to generate password again\nEnter another digit if you want to stop creating password\n";
            cin >> numberChar;
            cin.ignore();
            if (numberChar == 1)
                Record::generatePassword();
            return "";
    }

    cout
            << "Enter 1 if you want to have special symbols\nEnter 2 if you don't want to have special symbols\nEnter 0 if you want to want to stop generating password\n";
    cin >> specialSymbols;
    cin.ignore();

    switch (specialSymbols) {
        case 1:
            characters += specialChar;
            break;
        case 2:
            break;
        case 0:
            return "";
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to generate password again\nEnter another digit if you want to stop creating password\n";
            cin >> numberChar;
            cin.ignore();
            if (numberChar == 1)
                Record::generatePassword();
            return "";
    }

    string password;

    for (int i = 0; i < numberChar; i++) {
        auto random = rand() % characters.size();
        password += characters[random];
    }

    return password;
}