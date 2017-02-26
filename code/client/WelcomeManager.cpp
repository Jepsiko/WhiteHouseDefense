//
//

#include "WelcomeManager.h"

WelcomeManager::WelcomeManager(char *ip_addr, App* my_app) : AbstractManager(ip_addr, my_app) {

}

void WelcomeManager::run() {
    welcomeUI.display();
    int choice = welcomeUI.select();

    if (choice == 1) {
        LoginManager * loginManager = new LoginManager(5555, server_ip_address, master_app);
        master_app->transition(loginManager);
    } else if (choice == 2) {
        RegisterManager * registerManager = new RegisterManager(5555, server_ip_address, master_app);
        master_app->transition(registerManager);
    } else if (choice == 3) {
        //
    }
}
