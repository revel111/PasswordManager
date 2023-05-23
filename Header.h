#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using std::cout, std::cin, std::string, std::vector, std::map, std::getline;

class Record {
    string name;
    string text;
    string service;
    string login;
public:
    string getName();

    Record(string nameN);

    string toString();

    static void addRecord();

    static string generatePassword();
};

class Manager {
    static map<string, vector<Record>> data;
    static vector<Record> passwordVector;
    static vector<string> categoryVector;
public:
    vector<Record> getPasswordVector();

    vector<string> getCategoryVector();

    static map<string, vector<Record>> getData();

    static void printCategories();

    static void addCategory();

    static void deleteCategory();
};