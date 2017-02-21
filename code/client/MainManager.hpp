#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "NetworkedManager.hpp"

class MainManager {

private:
	MainUI mainUI;
	char* server_ip_adress;
	int player_id;
	std::string username;

	void start_display();

public:
    MainManager(char* ip_addr, int id, std::string username);
};

#endif