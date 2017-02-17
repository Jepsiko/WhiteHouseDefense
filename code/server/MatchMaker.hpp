#ifndef MATCHMAKER_HPP
#define MATCHMAKER_HPP

#include "Server.hpp"
#include "PendingMatch.h"
#include "MatchmakingCommand.hpp"
#include "../common/Strings.hpp"
#include <string>

class MatchMaker : public Server {

private:

    PendingMatch classicPendingMatch;
    PendingMatch timedPendingMatch;
    PendingMatch teamPendingMatch;

    void announceMatchStart(PlayerConnection playerConnection);
    void launchGameServer(PendingMatch match);
    void launchMatch(PendingMatch match);
    PendingMatch& getMatch(std::string mode);
    void addPlayerToPendingMatch(PlayerConnection player_connection, std::string mode);
    void get_and_process_command(int socket_fd);


public:

    MatchMaker(int port);

    void run();
};

#endif
