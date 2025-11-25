#include "Services.h"
#include <iostream>
#include <limits>
#include "../parcel/Parcel.h"

void showServiceMenu(const std::string& userLogin) {
    int choice = 0;

    // displays the main service menu for the authenticated user
    std::cout << "\n=== Welcome, " << userLogin << " ===\n";

    // continuously displays menu options until logout
    while (true) {
        std::cout << "\nPlease choose a service:\n";
        std::cout << "1. Create a parcel\n";
        std::cout << "2. View branch offices\n";
        std::cout << "3. Track a parcel\n";
        std::cout << "4. Logout\n";
        std::cout << "Your choice: ";
        
        // reads user input and clears the buffer to prevent errors
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // handles navigation based on user selection
        switch (choice) {
            case 1:
                std::cout << "🚀 Starting parcel creation module...\n";
                createParcel(userLogin);
                break;
            case 2:
            case 3:
                std::cout << "⚠️ Function currently unavailable.\n";
                break;
            case 4:
                std::cout << "Logging out...\n";
                return;
            default:
                std::cout << "❌ Invalid choice. Try again.\n";
        }
    }
}
