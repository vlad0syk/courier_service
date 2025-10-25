#ifndef AUTH_H
#define AUTH_H

#include <string>
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

#endif
