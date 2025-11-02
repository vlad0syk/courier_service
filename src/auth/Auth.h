#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include "../../include/Role.h"

//User structure
struct User {
    std::string login; 
    std::string password;
    Role role;
};

//Authorization/registration functions
std::string loginUser();
void registerUser();

//Utility functions
std::vector<User> loadUsers(const std::string& filepath);
void saveUser(const User& user, const std::string& filepath);
bool isUsernameTaken(const std::vector<User>& users, const std::string& login);
bool validateCredentials(const std::vector<User>& users, const std::string& login, const std::string& password);

#endif
