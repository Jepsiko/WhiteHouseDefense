#include "AbstractTower.hpp"

AbstractTower::AbstractTower(Position position, int price, int radius):
        position(position), price(price), quadrant(0), radius(radius) {
    AbstractTower::setQuadrant();
}

void AbstractTower::setQuadrant() {

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
