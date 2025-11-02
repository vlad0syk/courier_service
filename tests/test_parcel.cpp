#include <catch2/catch_all.hpp>
#include "../src/parcel/Parcel.h"
#include "../src/utils/FileUtils.h"
#include "../src/utils/DeliveryTypeUtils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>

TEST_CASE("generateParcelID creates incremental IDs", "[Parcel]") {
    createDirectory("data");
    std::ofstream clearFile("data/parcels.txt", std::ios::trunc);
    clearFile.close();

    std::string id1 = generateParcelID();
    std::ofstream("data/parcels.txt", std::ios::app) << id1 << "\n";
    std::string id2 = generateParcelID();

    REQUIRE(id1 == "P0001");
    REQUIRE(id2 == "P0002");
}

TEST_CASE("saveParcel correctly writes to file", "[Parcel]") {
    createDirectory("data");
    const std::string testFile = "data/parcels.txt";
    std::remove(testFile.c_str());

    Parcel parcel{
        "P0001", "vlad", "anna", "Kyiv, 123 Street", 2.5, DeliveryType::EXPRESS
    };

    saveParcel(parcel);

    std::ifstream fin(testFile);
    REQUIRE(fin.good());

    std::string line;
    std::getline(fin, line);
    fin.close();

    REQUIRE(line.find("P0001") != std::string::npos);
    REQUIRE(line.find("vlad") != std::string::npos);
    REQUIRE(line.find("express") != std::string::npos);
}

TEST_CASE("createParcel works with user input", "[Parcel]") {
    std::istringstream input(
        "recipient_user\n"
        "Lviv, Some Street 45\n"
        "3.2\n"
        "standard\n"
    );
    std::ostringstream output;

    std::streambuf* cinBuf = std::cin.rdbuf(input.rdbuf());
    std::streambuf* coutBuf = std::cout.rdbuf(output.rdbuf());

    createParcel("test_sender");

    std::cin.rdbuf(cinBuf);
    std::cout.rdbuf(coutBuf);

    std::string result = output.str();
    REQUIRE(result.find("Parcel created successfully") != std::string::npos);

    std::ifstream fin("data/parcels.txt");
    REQUIRE(fin.good());

    std::string lastLine, line;
    while (std::getline(fin, line)) {
        if (!line.empty()) lastLine = line;
    }
    fin.close();

    REQUIRE(lastLine.find("test_sender") != std::string::npos);
    REQUIRE(lastLine.find("standard") != std::string::npos);

}
