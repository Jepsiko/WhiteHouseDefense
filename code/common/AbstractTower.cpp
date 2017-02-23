#include "AbstractTower.hpp"
#include "Map.hpp"
#include "Constants.h"

AbstractTower::AbstractTower(Position position, int price, int radius):
        position(position), price(price), quadrant(computeQuadrant()), radius(radius) {
}

const int AbstractTower::computeQuadrant() {
    int realY = SIZE - position.getY();
    int realX = position.getX();

    // La diagonale croissante est celle qui respecte y = x,
    // et la diagonale decroissante est celle qui respecte y = -x
    bool aboveGrowingDiagonal = realY > realX;
    bool aboveDecreasingDiagonal = realY > -realX;

    if (aboveGrowingDiagonal && aboveDecreasingDiagonal){
        return NORTH;
    } else if (!aboveGrowingDiagonal && !aboveDecreasingDiagonal){
        return SOUTH;
    } else if (aboveGrowingDiagonal && !aboveDecreasingDiagonal){
        return WEST;
    } else {
        return EAST;
    }
}

int AbstractTower::getOwner() const { return quadrant; }

void AbstractTower::setOwner(int newOwner) { quadrant = newOwner; }

const int AbstractTower::getPrice() const { return price; }

int AbstractTower::getRadius() const { return radius; }

void AbstractTower::setRadius(int newRadius) { radius = newRadius; }

Position AbstractTower::getPosition() const { return position; }

void AbstractTower::setPosition(Position newPosition) { position = newPosition; }

std::string AbstractTower::serialize() {

    std::string serialized_me;

    serialized_me += std::to_string(quadrant) + "," + std::to_string(price) + "," +
                     std::to_string(radius) + ","/* + TODO:position.serialize()*/ + ";";

    return serialized_me;
}

int AbstractTower::getQuadrant() const {
    return quadrant;
}