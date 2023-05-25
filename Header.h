#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <thread>
#include <chrono>
#include <fstream>
#include <iterator>
//#include <utility> //xzz

using std::cout, std::cin, std::string, std::vector, std::map, std::getline;

class Record {
    string name;
    string text;
    string service;
    string login;
public:
    string getName();
    string getText();
    string getService();
    string getLogin();

    Record(string nameN);

    Record(string nameN, string textN, string serviceN, string loginN);

    Record(string nameN, string textN);

    Record(string nameN, string textN, string serviceOrLogin, int ch);

    friend std::ostream &operator<<(std::ostream &, const Record &);

    static void addRecord();

    static string generatePassword();
};

class Manager {
    static map<string, vector<Record>> data;
    static string path;
public:
    static map<string, vector<Record>> getData() {
        return data;
    }

    static void setPath(string str) {
        path = std::move(str);
    }

    static void printCategories();

    static void printData();

    static void deleteRecord();

    static void insertInData(const string &key, const Record &record);

    static void addCategory();

    static string addCategory(bool f);

    static void deleteCategory();

    static bool checkPassword();

    static string writeInFile();

    static void sortData();

    static void findRecord();

    static void printInitials(const string& str);
};