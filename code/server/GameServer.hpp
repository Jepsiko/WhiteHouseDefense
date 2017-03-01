
#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "Server.hpp"
#include "../common/GameState.hpp"
#include "PendingMatch.h"
#include "PlayerConnection.hpp"
#include "../common/Strings.hpp"
#include "TowerCommand.h"
#include "GameEngine.hpp"
#include <time.h>
#include "../common/Constants.h"
#include "../common/Tools.hpp"

static const int NUM_PLAYERS = 4;

static const int NUM_SECONDS_TO_PLACE_TOWER = 30;
static const int INTERVAL_BETWEEN_SENDS_IN_MS = 200;

class   GameServer : public Server {
private:


    std::string mode;

    // Je l'ai mis comme pointeur, car je veux seulement l'initialiser dans la methode run.
    // Si je l'initialise dans le constructeur, je suis obligé de garder la seed dans un field
    // pour l'envoyer au client (pendant la methode run), ce que je veux éviter
    GameEngine * gameEngine;
    std::vector<PlayerConnection> playerConnections;
    int client_sockets[4];

    pthread_t spectatorJoinThread;


    void sendGameStateToPlayer(PlayerConnection &connection);
    void get_and_process_command(int client_socket_fd, char buffer[]);
    void addTowerInGameState(TowerCommand &command);

    bool isFinishedClassic();    //pour le mode classic
    bool isFinishedCoop();       //pour le mode par équipe
    bool isFinishedVsTime();     //pour le mode contre la montre

public:

    GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode);

    void getReceivedChanges();


    void processClientCommands();

    void sendGameStateToPlayers();

    void runWave();

    void run();

    void handleEndOfGame();

    void sendEndToPlayer(PlayerConnection &connection);

    void sendWinnerToPlayer(PlayerConnection &connection);
    void sendMapSeedToClients(unsigned int mapSeed);

    void sendTowerPhase();
    void sendWavePhase();

    void sendQuadrantToClients();

    void createPlayerStates() const;

    int connectToAccountServer();
    void updatePlayerStatsOnAccountServer();

    void deleteTowerInGameState(TowerCommand command);

    void sendInitialGameState();

    void upgradeTowerInGameState(TowerCommand command);

    void runGame();

    void startSpectatorThread() const;

    void stopSpectatorThread();

    static void *staticJoinSpectatorThread(void *);

    void *getAndProcessSpectatorJoinCommand();
};

#endif