

#include "RegisterUI.hpp"
#include "Drawing.hpp"
#include "unistd.h"

RegisterUI::RegisterUI() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
}

void RegisterUI::ask_username() {
    std::cout << "   Enter a username:     ( 16 characters max. )" << std::endl << "   ";
    std::cin >> username_entry;
    std::cin.clear();
    std::cin.ignore();
}

void RegisterUI::ask_password() {
    std::cout << "   Enter a password:" << std::endl << "   ";
    std::cin >> password_entry;
    std::cin.clear();
    std::cin.ignore();
    password_entry = crypt(password_entry.c_str(), "g4");
    for (unsigned i = 0; i < password_entry.length(); i++) {
        if (password_entry[i] == ',' || password_entry[i] == ';') password_entry.erase(i);
    }
}


void RegisterUI::displayError() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    std::cout << "   Error : This username is already used or is not valid \n";
}

void RegisterUI::display() {
    ask_username();
    ask_password();
}