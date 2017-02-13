//
// Created by david on 12/02/17.
//

#include "RegisterManager.hpp"


void RegisterManager::registerUser() {
    Credentials toRegister;
    bool correctCredentials = false;
    while( !registered ){
        registerUI.display();
        if (checkCredentialsValidity(registerUI.get_username_entry(), registerUI.get_password_entry())) {
            correctCredentials = true;
        }
        else{
            registerUI.displayError();
        }
    }
    toRegister.setUsername(registerUI.get_username_entry());
    toRegister.setPassword(registerUI.get_password_entry());

    if (attemptRegister(toRegister)){
        std::cout<< "Your account was successfully registered, you can now login normally.\n";
    }else{
        registerUI.displayError();
    }

}

bool RegisterManager::attemptRegister(Credentials credentials){
    char server_response[10];
    std::string message = "register," + credentials.getUsername() + "," + credentials.getPassword() + ";";

    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);

    if (server_response[0] == '1') {
        return true;
    }
    return false;
}


bool RegisterManager::checkCredentialsValidity(Credentials credentials) {
    bool credentialsValidity;

    if ((credentials.getUsername().length() == 0 || credentials.getPassword().size() == 0)) {
        // check for spaces in username || password
        for (int i = 0 ; i < credentials.getUsername().length() ;i++){
            if(credentials.getUsername() == " " || credentials.getPassword() == " "){
                credentialsValidity = false;
            }
        }
    } else {
        credentialsValidity = true;
    }

    return credentialsValidity;
}