#pragma once
#include <string>

enum class Gender {
    Male,
    Female,
    KeepSecret
};

struct User {
    std::string nickname;
    Gender gender = Gender::KeepSecret;
    // ...
};
