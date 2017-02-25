#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"
#include "../common/Direction.h"

#define STEP_DURATION 1000


class GameEngine {

private:
    GameState gameState;

    int numStepsDone;
    int numOfPNJsPerWave;

    Timer timer;


    PlayerState &getPlayerStateForWave(Wave &wave);
public:

    GameEngine();

    bool update();

    GameState &getGameState() const;
    void createWaves();
    void updateWaves();
    void dealDamage(std::vector<Wave> &waves);
    void movePNJsInWaves(std::vector<Wave> &waves);
    void movePNJsInWave(Wave &wave);
    void removeDeadPNJs();

    void updatePlayerStates();
    void dealDamageToBase(std::vector<PlayerState> &playerStates);
    void giveGold(PlayerState& playerState);

    Wave& getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves);

    void increaseWaveDifficulty();

    bool isGameFinished();
    std::string * serializeGameState();


};


#endif //PROJET_GAMEENGINE_HPP
