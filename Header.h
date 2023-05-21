#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <vector>
#include <bits/stdc++.h>

using std::cout, std::cin, std::string, std::vector;

class Password {
    string name;
    string text;
    string category;
    string login;
    string service;
public:
    string getName();

    Password(string nameN);

    static void createPassword();

    static string generatePassword();
};

class Manager {
    static vector<Password> passwordVector;
    static vector<string> categoryVector;
public:
    static vector<Password> getPasswordVector();

    static vector<string> getCategoryVector();
    static void addCategory();
    static void deleteCategory();
};