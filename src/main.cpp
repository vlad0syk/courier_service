#include <iostream>
#include "auth/Auth.h"

int main() {
    while (true) {
        std::string userLogin = loginUser();
        if (!userLogin.empty()) {
            std::cout << "You are logged in as: " << userLogin << "\n";
            break;
        } else {
            std::cout << "Please try again.\n";
        }
    }
}