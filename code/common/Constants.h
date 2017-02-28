#ifndef PROJET_CONSTANTS_H
#define PROJET_CONSTANTS_H

static const int NORTH = 0;
static const int EAST = 1;
static const int SOUTH = 2;
static const int WEST = 3;
static const int DIRECTIONS[] = {NORTH, EAST, SOUTH, WEST};

static const int PNJ_STARTING_HEALTHPOINTS= 100;
static const int PNJ_STARTING_MOVESPEED = 100;

static const int PNJ_VALUE = 10;
static const int PNJ_DAMAGE= 10;

static const char PLACING_TOWER[2] = "t";
static const char WAVE[2] = "w";

static const int GOLD_EARNED_BY_SECOND= 1;

// Ça doit être 100.0, sinon c'est une division entiere et le resultat est 0
static const float PERCENTAGE_RECOVERED_MONEY= (const float) (50 / 100.0);

const int ATTACK_TOWER_PRICE = 10;
const int ATTACK_TOWER_RANGE = 4;
const int ATTACK_TOWER_DAMAGE = 20;

#endif //PROJET_CONSTANTS_H
