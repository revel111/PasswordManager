#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
//#include <utility> //xzz

using std::cout, std::cin, std::string, std::vector, std::map, std::getline;

class Record {
    string name;
    string text;
    string service;
    string login;
public:
    string getName();

    Record(string nameN);

    Record(string nameN, string textN, string serviceN, string loginN);

    Record(string nameN, string textN);

    Record(string nameN, string textN, string serviceOrLogin, int ch);

    friend std::ostream &operator<<(std::ostream &, const Record &);

    static void addRecord();

    static void deleteRecord();

    static string generatePassword();
};

class Manager {
    static map<string, vector<Record>> data;
public:

    static map<string, vector<Record>> getData();

    static void printCategories();

    static void printData();

    static void insertInData(const string &key, const Record &record);

    static void addCategory();

    static void deleteCategory();
};