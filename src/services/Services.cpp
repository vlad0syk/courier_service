#include "Services.h"
#include <iostream>

void showServiceMenu(const std::string& userLogin) {
    int choice = 0;

    std::cout << "\n=== Welcome, " << userLogin << " ===\n";

    while (true) {
        std::cout << "\nPlease choose a service:\n";
        std::cout << "1. Create a parcel\n";
        std::cout << "2. View branch offices\n";
        std::cout << "3. Track a parcel\n";
        std::cout << "4. Logout\n";
        std::cout << "Your choice: ";
        
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "🚀 Starting parcel creation module...\n";
                //there would be code to create a parcel
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
