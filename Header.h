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

/// The class which represent password/record in our files.
class Record {
    string name;
    string text;
    string service;
    string login;
public:
    /** Getter for name because of private field. @return string*/
    auto getName() -> string;

    /** Getter for text because of private field. @return string*/
    auto getText() -> string;

    /** Getter for service because of private field. @return string*/
    auto getService() -> string;

    /** Getter for login because of private field. @return string*/
    auto getLogin() -> string;

    /** Setter for name because of private field. @return string*/
    auto setName(string name) -> void;

    /** Setter for text because of private field. @return void */
    auto setText(string text) -> void;

    /** Setter for service because of private field. @return void */
    auto setService(string service) -> void;

    /** Setter for login because of private field. @return void */
    auto setLogin(string login) -> void;

    /** Constructor when we have both service and login. @return bool */
    Record(string nameN, string textN, string serviceN, string loginN);

    /** Comparator for sorting records by their names. @return bool */
    static auto compareStringsName(const Record &first, const Record &second) -> bool;

    /** Comparator for sorting records by their passwords. @return bool */
    static auto compareStringsText(const Record &first, const Record &second) -> bool;

    /** Comparator for sorting records by their services. @return bool */
    static auto compareStringsService(const Record &first, const Record &second) -> bool;

    /** Comparator for sorting records by their logins. @return bool */
    static auto compareStringsLogin(const Record &first, const Record &second) -> bool;

    /** Function for printing record. @return void */
    auto toString() const -> void;

    /**
     * Function which allows to create new records based on our preferences.
     * First of all we have to write unique name of our record, then we have option to generate password with the help of function generatePassword or we can create own password.
     * Another option is to choose category or we can simply create new category. The last two propositions are to provide name of service/website for which this record is.
     * After creation, record will be stored into "map<string, vector<Record>> data" and then encrypted into file.
     * @see generatePassword();
     * @see Manager::addCategory(bool f);
     */
    static auto addRecord() -> void;

    /**
     * Function which allows to generate new password based on our preferences.
     * We have many ways to customize it such as length of a password (5-20 characters), lowercase or uppercase letters and special symbols. After generation we ask user
     * whether he likes this password or not. After choosing option "yes", we return password to function addRecord() and continue to create record.
     * After choosing option "no", user has opportunity to regenerate password.
     * @see addRecord();
     * @return string (new generated password)
     */
    static auto generatePassword() -> string;
};

/// The class which represent kind of storage for our data, so it has many functions which allows to manipulate with our records.
class Manager {
    static map<string, vector<Record>> data;
    static string path;
public:
    /** Getter for data of our program because of private field. @return map with all data*/
    static auto getData() -> map<string, vector<Record>>;

    /** Function which prints all categories of records. @return void*/
    static auto printCategories() -> void;

    /** Function which prints all records with its categories. @return void*/
    static auto printData() -> void;

    /** Function which allows to delete record by providing its name. @return void*/
    static auto deleteRecord() -> void;

    /** Function which allows to insert records and category. @return void  */
    static auto insertInData(const string &key, const Record &record) -> void;

    /** Function which allows to create new category by providing its name. @return void*/
    static auto addCategory() -> void;

    /**
     * Function which allows to delete category by providing its name.
     * It is worth to mention that with category we delete all records from this category.
     * @return void
    */
    static auto deleteCategory() -> void;

    /** Function which checks if user enters correct administrator's password. @return void*/
    static auto checkPassword() -> void;

    /**
     * Function which saves and encrypt using XOR encryption edited map<string, vector<Record>> data.
     * map<string, vector<Record>> data can be modified during operations such as adding, deleting and sorting.
     * @see Record::addRecord();
     * @see addCategory();
     * @see deleteRecord();
     * @see deleteCategory();
     * @see editRecord();
     * @see sortData();
     * @return void
    */
    static auto writeInFile() -> void;

    /**
     *  Function which reads encrypted file provided by user. It checks path to file and asks user to provide path again if any problem occurs.
     *  After checking correctness of path, it decrypt data and write it into memory, so we will be able to work with data.
     *  @see start();
     *  @return void
     */
    static auto readFile() -> void;

    /**
     * Function which allows to sort records.
     * We have to choose parameter by which we want to sort our records like by name, password, website/service or login.
     * @see Record::compareStringsName(const Record &first, const Record &second);
     * @see Record::compareStringsText(const Record &first, const Record &second);
     * @see Record::compareStringsService(const Record &first, const Record &second);
     * @see Record::compareStringsLogin(const Record &first, const Record &second);
     * @return void
    */
    static auto sortData() -> void;

    /**
     * Function which allows to find record by parameters such as category, name, password, service/website or login,
     * After finding matched record, function prints it.
     * @return void
     */
    static auto findRecord() -> void;

    /**
     * Function which allows to edit records.
     * We have to enter a name of a records we want to delete and then we have many options how exactly we want to edit record like name, password, website/service or login.
     * @return void
     */
    static auto editRecord() -> void;

    /**
     * Function which starts our program.
     * It asks for administrator's password, for specifying source file of records and it has little presentation of the name of this project.
     * Another important aspect is that program registers last attempt of logging into program and write time into file with passwords, splitting time into lines.
     * @see checkPassword();
     * @return void
     */
    static auto start() -> void;
};