//
// Created by jepsiko on 03/03/17.
//

#include "SniperTower.hpp"
#include <cmath>

SniperTower::SniperTower(const Position &position) :
        AttackTower(position, SNIPER_TOWER_DAMAGE, SNIPER_TOWER_PRICE, SNIPER_TOWER_RANGE) {}

const std::vector<PNJ *>& SniperTower::shoot(Wave &wave) {
    PNJ *target;
    std::vector<PNJ *> killed;
    target = get_closest_pnj(wave);
    if ((target != nullptr) && (!target->isInPlayerBase()) && (target->getHealthPoints() > 0)) {
        dealDamageTo(*target);
        if (target->getHealthPoints() <= 0) {
            killed.push_back(target);
        }
    }
    return killed;
}

std::string SniperTower::serialize() {
    /*
     * Une SniperTower sérialisée est comme ceci : "SniperTower,x,y;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    //serialized_me.insert(0, std::to_string(damageAmount));
    serialized_me.insert(0, SNIPER_TOWER_STR);

    return serialized_me;
}

PNJ *SniperTower::get_closest_pnj(Wave &wave) {
    int dist;
    int best_dist = 1 << 30;
    PNJ *closest_pnj = nullptr;
    for (PNJ &pnj: wave.getPnjs()) {
        int distance_x = getPosition().getX() - pnj.getPosition().getX();
        int distance_y = getPosition().getY() - pnj.getPosition().getY();

        dist = ((distance_x) * (distance_x)) + (distance_y * distance_y);
        if (dist < best_dist) {
            best_dist = dist;
            closest_pnj = &pnj;
        }
    }
    if (sqrt(best_dist) > getRange()) {
        closest_pnj = nullptr;

    }

    return closest_pnj;
}

std::string SniperTower::getType() {
    return SNIPER_TOWER_STR;
}

