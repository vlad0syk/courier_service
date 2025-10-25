#include <iostream>
#include "auth/Auth.h"
#include "services/Services.h"

int main() {
    while (true) {
        std::string userLogin = loginUser();
        if (!userLogin.empty()) {
            std::cout << "You are logged in as: " << userLogin << "\n";
            showServiceMenu(userLogin);
        } else {
            std::cout << "Please try again.\n";
        }
    }
}