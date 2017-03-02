//
// Created by jepsiko on 02/03/17.
//

#include "GunTower.hpp"
#include <cmath>

GunTower::GunTower(Position position) :
        AttackTower::AttackTower(position, GUN_TOWER_DAMAGE, GUN_TOWER_PRICE, GUN_TOWER_RANGE) {}

bool GunTower::shoot(Wave &wave) {
    PNJ *my_target;
    bool killed = false;
    my_target = get_closest_pnj(wave);
    if ((my_target != nullptr) && (!my_target->isInPlayerBase()) && (my_target->getHealthPoints() > 0)) {
        dealDamageTo(*my_target);
        if (my_target->getHealthPoints() <= 0) {
            killed = true;
        }
    }
    return killed;
}

std::string GunTower::serialize() {
    /*
     * Une GunTower sérialisée est comme ceci : "GunTower,x,y;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    //serialized_me.insert(0, std::to_string(damageAmount));
    serialized_me.insert(0, "GunTower");

    return serialized_me;
}

PNJ *GunTower::get_closest_pnj(Wave &wave) {
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
