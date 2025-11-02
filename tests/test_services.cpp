#include <catch2/catch_all.hpp>
#include "../src/services/Services.h"
#include <sstream>
#include <iostream>

bool mockCalled = false;
void createParcel(const std::string& userLogin) {
    mockCalled = true;
}

TEST_CASE("Service menu - invalid and logout options", "[Services]") {
    std::istringstream input("9\n4\n");
    std::ostringstream output;

    std::streambuf* cinBuf = std::cin.rdbuf(input.rdbuf());
    std::streambuf* coutBuf = std::cout.rdbuf(output.rdbuf());

    showServiceMenu("vlad");

    std::cin.rdbuf(cinBuf);
    std::cout.rdbuf(coutBuf);

    std::string result = output.str();

    REQUIRE(result.find("Invalid choice") != std::string::npos);
    REQUIRE(result.find("Logging out") != std::string::npos);
}

TEST_CASE("Service menu - unavailable options", "[Services]") {
    std::istringstream input("2\n3\n4\n");
    std::ostringstream output;

    std::streambuf* cinBuf = std::cin.rdbuf(input.rdbuf());
    std::streambuf* coutBuf = std::cout.rdbuf(output.rdbuf());

    showServiceMenu("test_user");

    std::cin.rdbuf(cinBuf);
    std::cout.rdbuf(coutBuf);

    std::string result = output.str();

    REQUIRE(result.find("Function currently unavailable") != std::string::npos);
}

TEST_CASE("Service menu - calls parcel creation", "[Services]") {
    mockCalled = false;
    std::istringstream input("1\n4\n");
    std::ostringstream output;

    std::streambuf* cinBuf = std::cin.rdbuf(input.rdbuf());
    std::streambuf* coutBuf = std::cout.rdbuf(output.rdbuf());

    showServiceMenu("tester");

    std::cin.rdbuf(cinBuf);
    std::cout.rdbuf(coutBuf);

    REQUIRE(mockCalled == true);
}
