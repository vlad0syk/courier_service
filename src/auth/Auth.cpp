#include "Auth.h"
#include "../utils/RoleUtils.h"
#include "../utils/FileUtils.h"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

static const std::string USERS_FILE = "data/users.txt";

std::vector<User> loadUsers(const std::string& filepath) {
    std::vector<User> users; 
    std::ifstream file(filepath);

    if (!file.is_open()) {
        if (filepath == USERS_FILE) {
             std::cerr << "⚠️ Failed to open " << filepath << ". Creating a new one...\n";
             createDirectory("data");
             std::ofstream newFile(filepath);
             newFile.close();
        }
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        User user;
        std::string roleStr;

        std::getline(ss, user.login, ';');
        std::getline(ss, user.password, ';');
        std::getline(ss, roleStr, ';');

        try {
            user.role = stringToRole(roleStr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Warning: " << e.what() << ". Skipping user.\n";
            continue;
        }

        if (!user.login.empty()) {
            users.push_back(user);
        }
    }

    file.close();
    return users;
}

void saveUser(const User& user, const std::string& filepath) {
    std::ofstream file(filepath, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "❌ Failed to open file for writing: " << filepath << "\n";
        return;
    }
    file << user.login << ";" << user.password << ";" << roleToString(user.role) << "\n";
    file.close();
}

bool isUsernameTaken(const std::vector<User>& users, const std::string& login) {
    for (const auto &u : users) {
        if (u.login == login) {
            return true;
        }
    }
    return false;
}

bool validateCredentials(const std::vector<User>& users, const std::string& login, const std::string& password) {
    for (const auto &u : users) {
        if (u.login == login && u.password == password) {
            return true;
        }
    }
    return false;
}


std::string loginUser() {
    std::vector<User> users = loadUsers(USERS_FILE);
    std::string login, password;

    std::cout << "\n=== Authentication ===\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "Your choice: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 2) {
        registerUser();
        return loginUser();
    }

    std::cout << "Login: ";
    std::getline(std::cin, login);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    if (validateCredentials(users, login, password)) {
        std::cout << "✅ Login successful. Welcome, " << login << "!\n";
        return login;
    }

    std::cout << "❌ Incorrect username or password.\n";
    return "";
}

void registerUser() {
    std::vector<User> users = loadUsers(USERS_FILE);
    User newUser;

    std::cout << "=== Register New User ===\n";
    std::cout << "Enter username: ";
    std::getline(std::cin, newUser.login);

    if (isUsernameTaken(users, newUser.login)) {
        std::cout << "❌ A user with that username already exists!\n";
        return;
    }
    
    std::cout << "Enter password: ";
    std::getline(std::cin, newUser.password);

    std::cout << "Enter role (client / courier / admin): ";
    std::string roleInput;
    std::getline(std::cin, roleInput);
    try {
        newUser.role = stringToRole(roleInput);
    } catch (const std::invalid_argument& e) {
        std::cout << "❌ Invalid role. User creation cancelled.\n";
        return;
    }

    saveUser(newUser, USERS_FILE);
    std::cout << "✅ Registration successful!\n";
}