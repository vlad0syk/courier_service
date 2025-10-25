#ifndef AUTH_H
#define AUTH_H

#include <string>

//User roles
enum class Role {CLIENT = 0, COURIER = 1, ADMIN = 2};

//User structure
struct User {
    std::string login; 
    std::string password;
    Role role;
};

//Authorization/registration functions
std::string loginUser();
void registerUser();

#endif
