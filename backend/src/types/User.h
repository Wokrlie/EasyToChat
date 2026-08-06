#pragma once
#include <string>

enum class Gender {
    Male,
    Female,
    KeepSecret
};

struct User {
    std::string username;
    std::string nickname;
    std::string password;
    Gender gender = Gender::KeepSecret;
    // ...
};
