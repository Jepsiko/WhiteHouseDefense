
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "FriendList.hpp"
#include "RankingManager.hpp"


MainManager::MainManager(char* ip_addr, int id) : server_ip_adress(ip_addr), player_id(id){
    std::cout << "this is your player id: " << player_id << std::endl; //print juste pour test que ca marche
    start_display();
}

void MainManager::start_display() {
    mainUI.display();
    switch (mainUI.select()) {
        case 1: {
            std::cout << "Game Launcher !" << std::endl;
            GameLauncher game = GameLauncher(5556, server_ip_adress);
            break;
        }
        case 2: {
            std::cout << "Profile !" << std::endl;
            ProfileManager profile = ProfileManager();
            break;
        }
        case 3: {
            std::cout << "Friendlist !" << std::endl;
            FriendList friendList = FriendList();
            break;
        }
        case 4: {
            RankingManager rankingManager(5555, server_ip_adress);
            break;
        }
        default: {
            std::cout << "Exit !" << std::endl;
            mainUI.exit();
            break;
        }
    }
}
