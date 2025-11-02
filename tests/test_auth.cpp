#include <catch2/catch_all.hpp>
#include "../src/auth/Auth.h"
#include "../src/utils/RoleUtils.h"
#include <fstream>

TEST_CASE("Username availability check", "[Auth]") {
    std::vector<User> users = {
        {"vlad", "1234", Role::CLIENT},
        {"admin", "root", Role::ADMIN}
    };

    REQUIRE(isUsernameTaken(users, "vlad") == true);
    REQUIRE(isUsernameTaken(users, "unknown") == false);
}

TEST_CASE("Credential validation", "[Auth]") {
    std::vector<User> users = {
        {"anna", "pass123", Role::CLIENT},
        {"bob", "qwerty", Role::COURIER}
    };

    REQUIRE(validateCredentials(users, "anna", "pass123") == true);
    REQUIRE(validateCredentials(users, "bob", "wrong") == false);
    REQUIRE(validateCredentials(users, "nonexistent", "123") == false);
}

TEST_CASE("Saving and loading users from file", "[Auth]") {
    const std::string testFile = "data/test_users.txt";
    std::remove(testFile.c_str());

    User user1{"maria", "1111", Role::CLIENT};
    User user2{"oleg", "2222", Role::ADMIN};

    saveUser(user1, testFile);
    saveUser(user2, testFile);

    std::vector<User> loaded = loadUsers(testFile);

    REQUIRE(loaded.size() == 2);
    REQUIRE(loaded[0].login == "maria");
    REQUIRE(loaded[1].role == Role::ADMIN);

    std::remove(testFile.c_str());
}
