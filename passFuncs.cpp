#include "Header.h"

Password::Password(std::string name) {
    this->name = name;
}

std::string Password::getName() {
    return name;
}

void Password::createPassword() {
    auto ch = 0;
    cout
            << "Enter 1 if you want to create your own password\nEnter 2 if you want to generate password\nEnter 0 if you want to want to stop creating password\n";
    cin >> ch;

    string password = "";

    switch (ch) {
        case 1:
            cout << "Enter a password. A number of characters should be 5-20\n";
            cin >> password;
            if (password.size() < 5 || password.size() > 20) {
                cout
                        << "Wrong input\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
                cin >> ch;
                if (ch == 1)
                    Password::createPassword();
                return;
            }
            break;
        case 2 :
            password = Password::generatePassword();
            break;
        case 0:
            return;
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to create password again\nEnter another digit if you want to stop creating password\n";
            cin >> ch;
            if (ch == 1)
                Password::createPassword();
            return;
    }

    if (password == "")
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

    cout << "The strength of your password is " << score
         << "/100 \nEnter 1 if you want to use this password\nEnter another digit if you want to try to create password again\n";
    cin >> ch;
    if (ch == 1) {
        Password::createPassword();
        return;
    }
}

string Password::generatePassword() {
    auto lowCase = "abcdefghijklmnopqrstuvwxyz";
    auto upCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    auto specialChar = "£$&()*+[]@#^-_!?";
    string characters = "0123456789";

    auto numberChar = 0;
    auto specialSymbols = -1;
    auto lowerUpper = -1;

    cout << "Enter number of characters 5-20\n";
    cin >> numberChar;

    if (numberChar < 5 || numberChar > 20) {
        cout
                << "Wrong input\nEnter 1 if you want to generate password again\nEnter another digit if you want to stop creating password\n";
        cin >> numberChar;
        if (numberChar == 1)
            Password::generatePassword();
        return "";
    }

    cout
            << "Enter 1 if you want to have lowercase and uppercase letters\nEnter 2 if you want to have only lowercase letters\nEnter 3 if you want to have only uppercase letters\nEnter 0 if you want to want to stop generating password\n";
    cin >> lowerUpper;

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
        case 0:
            return "";
        default:
            cout
                    << "Wrong input\nEnter 1 if you want to generate password again\nEnter another digit if you want to stop creating password\n";
            cin >> numberChar;
            if (numberChar == 1)
                Password::generatePassword();
            return "";
    }

    cout
            << "Enter 1 if you want to have special symbols\nEnter 2 if you don't want to have special symbols\nEnter 0 if you want to want to stop generating password\n";
    cin >> specialSymbols;

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
            if (numberChar == 1)
                Password::generatePassword();
            return "";
    }

    string password;

    for (int i = 0; i < numberChar; i++) {
        auto random = rand() % characters.size();
        password += characters[random];
    }

    cout << "Enter 1 if you want to regenerate password\nEnter another digit to use this password: " << password;
    cin >> numberChar;
    if (numberChar == 1) {
        Password::generatePassword();
        return "";
    }
    return password;
}