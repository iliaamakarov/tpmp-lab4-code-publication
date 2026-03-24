#include "auth.h"

AuthService::AuthService(Database& db) : db(db) {}

User AuthService::login(const std::string& username, const std::string& password) {
    User user;
    std::string sql = "SELECT role, crew_surname FROM USERS WHERE username = '" + username + "' AND password = '" + password + "';";
    
    auto results = db.query(sql);

    if (!results.empty()) {
        user.username = username;
        user.role = results[0][0];
        user.crew_surname = results[0][1];
        user.isAuthenticated = true;
    }
    
    return user;
}
