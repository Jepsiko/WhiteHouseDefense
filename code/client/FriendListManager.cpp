//
// Created by jurgen on 2/18/17.
//

#include "FriendListManager.hpp"

FriendListManager::FriendListManager(int port, char* address, int id): NetworkedManager(port, address), player_id(id)/*, friendList(getFriendList())*/{
    friendListProcess();
};

void FriendListManager::friendListProcess() {
    friendListUI.display();

    int choice = friendListUI.select();
    while ( choice!=8 ){
        if (choice == 1){
            std::cout<< "Your Friend list :  ";
            friendListUI.displayFriendList(getFriendList());
        }else if (choice == 2 ){
            std::cout<< "Your Friend requests :  ";
            friendListUI.displayFriendList(getFriendRequests());
        }else if (choice == 3) {
            std::cout<<"Your Friend Invitations :  ";
            friendListUI.displayFriendList(getPendingInvitations());

        }else if (choice == 4) {
            std::cout<<"Send Friend Request to : ";
            std::string toAdd ;
            std::cin >> toAdd;
            std::cout<<std::endl;
            if(sendFriendRequest(toAdd)){
                std::cout<<"Invitation Sent"<<std::endl;
            };

        }else if (choice == 5 ){
            std::cout<<"Remove Friend : ";
            std::string toRemove;
            std::cin >> toRemove;
            std::cout<<std::endl;
            if(removeFriend(toRemove)){
                std::cout<<"Friend removed successfully"<<std::endl;
            };
        }else if (choice == 6){
            std::cout<< "accept Friend : ";
            std::string toAccept;
            std::cin >> toAccept;
            std::cout<<std::endl;
            if (acceptFriendRequest(toAccept)){
                std::cout<<"Friend request accepted"<<std::endl;
            };
        }else if (choice == 7) {
            std::cout << "decline Friend : ";
            std::string toAccept;
            std::cin >> toAccept;
            std::cout << std::endl;
            if (declineFriendRequest(toAccept)) {
                std::cout << "Friend request declined" << std::endl;
            };
        }
        friendListUI.display();
        choice = friendListUI.select();

    }
    MainManager mainManager(ip_address, player_id); // Permet de revenir au main menu , je ne sais pas si
                                                    // c'est le meilleur moyen pour faire ca
}


std::string FriendListManager::getFriendList() {
    std::string message = "getFriendList;" + std::to_string(player_id)+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

std::string FriendListManager::getFriendRequests() {

    std::string message = "getFriendRequests;" + std::to_string(player_id)+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);

}
std::string FriendListManager::getPendingInvitations() {
    std::string message = "getPendingInvitations;" + std::to_string(player_id)+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

bool FriendListManager::sendFriendRequest(std::string toAdd){

    char server_response[10];
    std::string message = "addFriend;"+ std::to_string(player_id) + "," + toAdd+ ";" ;
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;
}

bool FriendListManager::removeFriend(std::string toRemove) {

    char server_response[10];
    std::string message = "removeFriend;"+ std::to_string(player_id) + "," + toRemove+ ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;

}
bool FriendListManager::acceptFriendRequest(std::string toAccept) {

    char server_response[10];
    std::string message = "acceptFriendRequest;"+ std::to_string(player_id) + "," + toAccept+ ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;

}


bool FriendListManager::declineFriendRequest(std::string toDecline) {

    char server_response[10];
    std::string message = "declineFriendRequest;"+ std::to_string(player_id) + "," + toDecline+ ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;

}