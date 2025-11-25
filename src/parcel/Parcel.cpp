#include "Parcel.h"
#include "../utils/FileUtils.h"
#include "../utils/DeliveryTypeUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <limits>

// generates a unique id for the new parcel based on the number of existing records
std::string generateParcelID() {
    // ensures the data directory exists
    createDirectory("data");

    // opens the file to count existing parcels
    std::ifstream fin("data/parcels.txt");
    int count = 0;
    std::string line;

    // counts non-empty lines to determine the next id number
    while (std::getline(fin, line)) {
        if (!line.empty()) count++;
    }

    fin.close();

    // formats the id as 'P' followed by 4 digits (e.g., P0001)
    std::ostringstream oss;
    oss << "P" << std::setw(4) << std::setfill('0') << (count + 1);
    return oss.str();
}

// saves parcel information to the text file
void saveParcel(const Parcel& parcel) {
    createDirectory("data");

    // opens file in append mode to add new data without erasing old data
    std::ofstream fout("data/parcels.txt", std::ios::app);
    if (!fout) {
        std::cerr << "❌ Error: cannot open parcels.txt for writing.\n";
        return;
    }

    // writes fields separated by semicolons
    fout << parcel.id << ";"
        << parcel.sender << ";"
        << parcel.recipient << ";"
        << parcel.address << ";"
        << parcel.weight << ";"
        << deliveryTypeToString(parcel.deliveryType) << "\n";

    fout.close();
}

// handles the user interface for creating a new parcel
void createParcel(const std::string& senderLogin) {
    Parcel parcel;
    // sets the logged-in user as the sender
    parcel.sender = senderLogin;

    std::cout << "\n=== Create New Parcel ===\n";

    std::cout << "Enter recipient name: ";
    std::getline(std::cin, parcel.recipient);

    std::cout << "Enter delivery address: ";
    std::getline(std::cin, parcel.address);

    std::cout << "Enter parcel weight (kg): ";
    // input validation loop for weight
    while (!(std::cin >> parcel.weight) || parcel.weight <= 0) {
        std::cout << "Invalid weight. Try again: ";
        // clears the error flag and ignores invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // clears the newline character left in the buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter delivery type (standard / express / overnight): ";
    std::string dt;
    std::getline(std::cin, dt);
    
    // tries to convert string to delivery type enum
    try {
        parcel.deliveryType = stringToDeliveryType(dt);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << "\n";
        // uses default type if input is invalid
        std::cout << "Using default: standard\n";
        parcel.deliveryType = DeliveryType::STANDARD;
    }

    // generates id and saves to file
    parcel.id = generateParcelID();

    saveParcel(parcel);

    std::cout << "✅ Parcel created successfully!\n";
    std::cout << "Your parcel ID: " << parcel.id << "\n";
}