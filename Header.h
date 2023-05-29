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

using std::cout, std::cin, std::string, std::vector, std::map, std::getline;
/// The class which represent password/record in our files
class Record {
    string name;
    string text;
    string service;
    string login;
public:
    /** Getter for name because of private field @return string*/
    string getName();
    /** Getter for text because of private field @return string*/
    string getText();
    /** Getter for service because of private field @return string*/
    string getService();
    /** Getter for login because of private field @return string*/
    string getLogin();
    /** Setter for name because of private field @return string*/
    void setName(string name);
    /** Setter for text because of private field */
    void setText(string text);
    /** Setter for service because of private field */
    void setService(string service);
    /** Setter for login because of private field */
    void setLogin(string login);

    Record(string nameN);

    /** Constructor when we have both service and login */
    Record(string nameN, string textN, string serviceN, string loginN);
    /** Constructor when we have only name and password itself */
    Record(string nameN, string textN);
    /** Constructor when we either service or login */
    Record(string nameN, string textN, string serviceOrLogin, int ch);
    /** Comparator for sorting records by their names */
    static bool compareStringsName(const Record &first, const Record &second);
    /** Comparator for sorting records by their passwords */
    static bool compareStringsText(const Record &first, const Record &second);
    /** Comparator for sorting records by their services */
    static bool compareStringsService(const Record &first, const Record &second);
    /** Comparator for sorting records by their logins */
    static bool compareStringsLogin(const Record &first, const Record &second);
    /** Overloaded operator for printing record */
    friend std::ostream &operator<<(std::ostream &, const Record &);

    friend std::ostream &operator<<(std::ostream &os, const std::pair<const string, vector<Record>> &pair);

    /**
     * Function which allows to create new records based on our preferences.
     * First of all we have to write unique name of our record, then we have option to generate password with the help of function generatePassword or we can create own password.
     * Another option is to choose category or we can simply create new category. The last two propositions are to provide name of service/website for which this record is.
     * After creation, record will be stored into "map<string, vector<Record>> data" and then encrypted into file.
     * @see generatePassword();
     * @see Manager::addCategory(bool f);
     */
    static void addRecord();
    /**
     * Function which allows to generate new password based on our preferences.
     * We have many ways to customize it such as length of a password (5-20 characters), lowercase or uppercase letters and special symbols. After generation we ask user
     * whether he likes this password or not. After choosing option "yes", we return password to function addRecord() and continue to create record.
     * After choosing option "no", user has opportunity to regenerate password.
     * @see addRecord();
     * @return string (new generated password)
     */
    static string generatePassword();
};

/// The class which represent kind of storage for our data, so it has many functions which allows to manipulate with our records
class Manager {
    static map<string, vector<Record>> data;
    static string path;
public:
    /** Getter for data of our program because of private field @return map with all data*/
    static map<string, vector<Record>> getData();

    static string getPath();

    static void setPath(string str);
    /** Function which prints all categories of records @return void*/
    static void printCategories();
    /** Function which prints all records with its categories @return void*/
    static void printData();
    /** Function which allows to delete record by providing its name @return void*/
    static void deleteRecord();
    /**
     * Function which allow to insert category without records @return void
     */
    static void insertInData(const string &key, const Record &record);
    /** Function which allows to create new category by providing its name @return void*/
    static void addCategory();
    /** Function which allows to create new category by providing its name and it also returns string because I use this function when user create new record @return string (new category)*/
    static string addCategory(bool f);
    /**
     * Function which allows to delete category by providing its name.
     * It is worth to mention that with category we delete all records from this category
     * @return void
    */
    static void deleteCategory();
    /** Function which checks if user enters correct administrator's password @return void*/
    static void checkPassword();
    /** Function which saves and encrypt using XOR encryption edited map<string, vector<Record>> data.
     * map<string, vector<Record>> data can be modified during operations such as adding, deleting and sorting
     * @see Record::addRecord();
     * @see addCategory();
     * @see addCategory(bool f);
     * @see deleteRecord();
     * @see deleteCategory();
     * @see editRecord();
     * @see sortData();
     * @return void
    */
    static void writeInFile();
    /**
     * Function which allows to sort records.
     * We have to choose parameter by which we want to sort our records like by name, password, website/service or login
     * @see Record::compareStringsName(const Record &first, const Record &second);
     * @see Record::compareStringsText(const Record &first, const Record &second);
     * @see Record::compareStringsService(const Record &first, const Record &second);
     * @see Record::compareStringsLogin(const Record &first, const Record &second);
     * @return void
    */
    static void sortData();
    /**
     * Function which allows to find record by parameters such as category, name, password, service/website or login,
     * After finding matched record, function prints it
     * @return void
     */
    static void findRecord();
    /**
     * Function which allows to edit records.
     * We have to enter a name of a records we want to delete and then we have many options how exactly we want to edit record like name, password, website/service or login
     * @return void
     */
    static void editRecord();
    /**
     * Function which starts our program.
     * It asks for administrator's password, for specifying source file of records and it has little presentation of the name of this project
     * @see checkPassword();
     * @return void
     */
    static void start(const string &str);
};