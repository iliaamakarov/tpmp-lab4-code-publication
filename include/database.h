#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

class Database {
public:
    Database(const std::string& db_path);
    ~Database();
    bool execute(const std::string& sql);
    std::vector<std::vector<std::string>> query(const std::string& sql);

private:
    sqlite3* db;
    static int callback(void* data, int argc, char** argv, char** azColName);
};

#endif // DATABASE_H
