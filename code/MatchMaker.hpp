#include "Server.hpp"
#include <iostream>
#include <string>

class MatchMaker : public Server {

private:
	int pendingMatches;

public:

	void getNewClients();

	void getPendingMatches(std::string mode);

	void addPendingMatch(std::string mode);
};
