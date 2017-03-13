#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "../NetworkedManager.hpp"
#include "../Abstract/AbstractManager.hpp"
#include "../App.hpp"
#include "MainUI.hpp"

class MainUI;

class MainManager : public NetworkedManager {

private:
	MainUI * mainUI;

public:
	MainManager(int port, App* my_app);
	void run() override;

    void handleUserMenuChoice();
    void handleGameModeChoice();
};

#endif