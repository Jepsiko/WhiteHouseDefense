#include "Manager.h"
#include "RegisterUI.hpp"
#include "Networking.h"
#include "Credentials.h"
#include "LoginManager.hpp"

class RegisterManager: public Manager {

private:
	RegisterUI registerUI;
    Credentials toRegister;

public:

	RegisterManager(int port, char* address);

	bool attemptRegister(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
	void registerUser();
};
