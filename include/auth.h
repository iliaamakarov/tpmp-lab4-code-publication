#ifndef AUTH_H
#define AUTH_H

#include "database.h"
#include <string>

struct User {
    std::string username;
    std::string role;
    std::string crew_surname;
    bool isAuthenticated = false;
};

class AuthService {
public:
    AuthService(Database& db);
    User login(const std::string& username, const std::string& password);
private:
    Database& db;
};

#endif // AUTH_H
