#include <crypt.h>
#include "Tools.hpp"

std::string bool_to_string(bool _bool){
    return _bool ? "true" : "false";
}

bool stringToBool(const std::string& str) {
    return str == "true";
}

std::string cryptPassword(std::string password){
    password = crypt(password.c_str(), "g4");
    for (unsigned i = 0; i < password.length(); i++) {
        if (password[i] == ',' || password[i] == ';') password.erase(i);
    }
    return password;
}