#ifndef PROJET_CONSTANTS_H
#define PROJET_CONSTANTS_H

#include <string>

static const int ACCOUNT_SERVER_PORT = 5555;
static const int MATCHMAKER_SERVER_PORT = 5556;


// Constant of the map

static const int NORTH = 0;
static const int EAST = 1;
static const int SOUTH = 2;
static const int WEST = 3;
static const int DIRECTIONS[] = {NORTH, EAST, SOUTH, WEST};
static const std::string QUADRANT_NAMES[4] = {"NORTH", "EAST", "SOUTH", "WEST"};

const static int PARTNERS[4] = {EAST, NORTH, WEST, SOUTH};

static const int NB_OF_MAPS = 3;

static const int TILES_SIZE = 16; // Size in pixel

static const int PATH_INT = 0;
static const int GRASS_INT = 1;
static const int BASE_INT = 2;
static const int GRASS_ROCK_INT = 3;
static const int TREE_INT = 4;
static const int PINE_INT = 5;
static const int SAND_INT = 6;
static const int PALMER_INT = 7;
static const int WATER_INT = 8;
static const int SAND_STONE_INT = 9;
static const int SAND_ROCK_INT = 10;
static const int WATER_ROCK_INT = 11;
static const int LAVA_INT = 12;
static const int SNOW_INT = 13;
static const int PINE_SNOW_INT = 14;
static const int DIRT_INT = 15;
static const int DIRT_ROCK_INT = 16;
static const int STONE_INT = 17;


// Constant of the pnj

static const int NB_OF_TYPE_OF_PNJ = 3;
static const int NUM_FREEZE_TICKS_FOR_PNJ = 20;

static const int COMMUNIST_PNJ_STARTING_HEALTHPOINTS = 150;
static const int COMMUNIST_PNJ_VALUE = 15;
static const int COMMUNIST_PNJ_DAMAGE = 3;

static const int MUSLIM_PNJ_STARTING_HEALTHPOINTS = 70;
static const int MUSLIM_PNJ_VALUE = 5;
static const int MUSLIM_PNJ_DAMAGE = 10;

static const int MEXICAN_PNJ_STARTING_HEALTHPOINTS = 100;
static const int MEXICAN_PNJ_VALUE = 10;
static const int MEXICAN_PNJ_DAMAGE = 5;


// Constant of the player

static const int PLAYER_STARTING_HP = 100;
static const int PLAYER_STARTING_MONEY = 200;

static const char PLACING_TOWER[2] = "t";
static const char WAVE[2] = "w";

static const int GOLD_EARNED_BY_TICK= 1;

static const float PERCENTAGE_RECOVERED_MONEY = (const float) (50 / 100.0);

// Constant of the towers
static const int NB_OF_TYPE_OF_TOWER = 4;

static const int GUN_TOWER_PRICE = 50;
static const int GUN_TOWER_RANGE = 4;
static const int GUN_TOWER_DAMAGE = 10;

static const int SNIPER_TOWER_PRICE = 100;
static const int SNIPER_TOWER_RANGE = 10;
static const int SNIPER_TOWER_DAMAGE = 5;

static const int SHOCK_TOWER_PRICE = 150;
static const int SHOCK_TOWER_RANGE = 3;
static const int SHOCK_TOWER_DAMAGE = 5;

static const int MISSILE_TOWER_PRICE = 200;
static const int MISSILE_TOWER_RANGE = 6;
static const int MISSILE_TOWER_DAMAGE = 15;
static const int MISSILE_TOWER_SUBRANGE = 3;
static const int MISSILE_TOWER_SUBDAMAGE = 5;


// Game Settings

static const int STEP_DURATION_IN_MS = 1000;
static const int INITIAL_NUMBER_OF_PNJS_PER_WAVE = 4;
static const int NUMBER_OF_PNJS_ADDED_PER_WAVE = 2;
static const int TIMED_GAME_DURATION = 120;

static const int NUM_PLAYERS = 4;
static const int NUM_SECONDS_TO_PLACE_TOWER = 10; //For the test
static const int INTERVAL_BETWEEN_SENDS_IN_MS = 200;
static const int INTERVAL_BETWEEN_PNJS_IN_WAVE_IN_MS = 1000;

#endif //PROJET_CONSTANTS_H
