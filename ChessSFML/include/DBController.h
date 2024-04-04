#pragma once
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>


class User {
public:
    std::string name;
    int id;

    User(std::string _name, int _id) : name(_name), id(_id) {}
};

static int callback(void* data, int argc, char** argv, char** azColName) {
    std::vector<User>* users = static_cast<std::vector<User>*>(data);

    int id = std::stoi(argv[0]);
    std::string name = argv[1];
    users->emplace_back(name, id);

    return 0;
}

class DBController {
private:
    sqlite3* db;
    char* errMsg;

public:
    std::vector<User> users;
    DBController() {
        std::ifstream file("source/users.db");
        if (!file.is_open())
        {
            std::ofstream oFile("source/users.db");
            oFile.close();

        }
        file.close();
        int rc = sqlite3_open("source/users.db", &db);
        if (rc != SQLITE_OK) {
            std::cerr << "������ ��� �������� ���� ������: " << sqlite3_errmsg(db) << std::endl;

            throw std::runtime_error("������ ��� �������� ���� ������");
        }
        std::cout << "���� ������ ������� �������." << std::endl;

        // �������� ������� �������������, ���� ��� �� ����������
        std::string createTableSQL = "CREATE TABLE IF NOT EXISTS Users("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Name TEXT NOT NULL);";
        rc = sqlite3_exec(db, createTableSQL.c_str(), nullptr, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "������ ��� �������� �������: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            throw std::runtime_error("������ ��� �������� �������");
        }
        std::cout << "������� ������� �������." << std::endl;
        fetchUsers();
    }


    ~DBController() {
        sqlite3_close(db);
    }

    void fetchUsers() {
        users.clear();
        std::string selectSQL = "SELECT ID, Name FROM Users;";
        int rc = sqlite3_exec(db, selectSQL.c_str(), callback, &users, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "������ ��� ������� �������������: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            throw std::runtime_error("������ ��� ������� �������������");
        }
        std::cout << "������������ ������� �������." << std::endl;
    }


    void createUser(const std::string& name) {
        std::string insertSQL = "INSERT INTO Users (Name) VALUES (\'"+name+"\');";
        int rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "������ ��� ���������� ������������: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            throw std::runtime_error("������ ��� ���������� ������������");
        }
        std::cout << "������������ ������� ��������." << std::endl;
        fetchUsers();
    }

    void deleteUser(int id) {
        std::string deleteSQL = "DELETE FROM Users WHERE ID = " + std::to_string(id) + ";";
        int rc = sqlite3_exec(db, deleteSQL.c_str(), nullptr, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "������ ��� �������� ������������: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            throw std::runtime_error("������ ��� �������� ������������");
        }
        std::cout << "������������ ������� ������." << std::endl;
        fetchUsers();
    }
};