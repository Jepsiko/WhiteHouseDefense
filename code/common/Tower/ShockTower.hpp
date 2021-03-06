#ifndef PROJET_SHOCKTOWER_HPP
#define PROJET_SHOCKTOWER_HPP


#include "AttackTower.hpp"

class ShockTower : public AttackTower {

public:
    ShockTower(const Position &position, int level);

    virtual ~ShockTower() = default;

    virtual const std::vector<PNJ *> shoot(Wave &wave, PlayerState& playerState) override;

    virtual std::string serialize() override;

    std::vector<PNJ*> get_targets(Wave& wave);

    std::string getType() override;
};


#endif //PROJET_SHOCKTOWER_HPP
