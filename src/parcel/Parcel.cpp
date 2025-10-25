#include "Parcel.h"
#include "../utils/FileUtils.h"
#include "../utils/DeliveryTypeUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <limits>


std::string generateParcelID() {
    createDirectory("data");

    std::ifstream fin("data/parcels.txt");
    int count = 0;
    std::string line;

    while (std::getline(fin, line)) {
        if (!line.empty()) count++;
    }

    fin.close();

    std::ostringstream oss;
    oss << "P" << std::setw(4) << std::setfill('0') << (count + 1);
    return oss.str();
}

void saveParcel(const Parcel& parcel) {
    createDirectory("data");

    std::ofstream fout("data/parcels.txt", std::ios::app);
    if (!fout) {
        std::cerr << "❌ Error: cannot open parcels.txt for writing.\n";
        return;
    }

    fout << parcel.id << ";"
        << parcel.sender << ";"
        << parcel.recipient << ";"
        << parcel.address << ";"
        << parcel.weight << ";"
        << deliveryTypeToString(parcel.deliveryType) << "\n";

    fout.close();
}

void createParcel(const std::string& senderLogin) {
    Parcel parcel;
    parcel.sender = senderLogin;

    std::cout << "\n=== Create New Parcel ===\n";

    std::cout << "Enter recipient name: ";
    std::getline(std::cin, parcel.recipient);

    std::cout << "Enter delivery address: ";
    std::getline(std::cin, parcel.address);

    std::cout << "Enter parcel weight (kg): ";
    while (!(std::cin >> parcel.weight) || parcel.weight <= 0) {
        std::cout << "Invalid weight. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter delivery type (standard / express / overnight): ";
    std::string dt;
    std::getline(std::cin, dt);
    try {
        parcel.deliveryType = stringToDeliveryType(dt);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << "\n";
        std::cout << "Using default: standard\n";
        parcel.deliveryType = DeliveryType::STANDARD;
    }

    parcel.id = generateParcelID();

    saveParcel(parcel);

    std::cout << "✅ Parcel created successfully!\n";
    std::cout << "Your parcel ID: " << parcel.id << "\n";
}
