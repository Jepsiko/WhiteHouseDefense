#ifndef MAP_HPP
#define MAP_HPP

#define SIZE 31 //Not > 41 because it's too big for a screen

#define GRASS "⬛"
#define PATH "⬜"
#define LIMIT "\033[34m❎\033[0m"
#define TOWER "\033[31m⬛\033[0m"
#define PNG "\033[33m⬛\033[0m"

#include <string>
#include <vector>
#include "Position.hpp"

class Map {
private:
    int matrix[SIZE][SIZE];

    void generateRandomMatrix();
    void initMap();
    bool generateQuarterMap(Position position);
    bool isNextToPath(Position position);
    void copyQuarter();
    void basicMap();

public:
    Map();
    Map(unsigned seed);
    void display();
    bool addTower(int x, int y, int typeOfTower);
    bool removeTower(int x, int y);
};

#endif
