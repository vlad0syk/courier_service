#include <algorithm>
#include <stdexcept>
#include <cctype>
#include "RoleUtils.h"

std::string roleToString(Role role) {
    switch (role) {
        case Role::CLIENT: 
            return "client";
        case Role::COURIER: 
            return "courier";
        case Role::ADMIN:
            return "admin";
        default:
            return "unknown";
    }
}

Role stringToRole(std::string roleStr) {
    std::transform(roleStr.begin(), roleStr.end(), roleStr.begin(), [](unsigned char c){ return std::tolower(c); });
    if (roleStr == "client") {
        return Role::CLIENT;
    }
    else if (roleStr == "courier") {
        return Role::COURIER;
    }
    else if (roleStr == "admin") {
        return Role::ADMIN;
    }
    throw std::invalid_argument("⚠️ Invalid role string: " + roleStr);
}