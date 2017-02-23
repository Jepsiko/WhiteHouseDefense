

#ifndef PROJET_PNJ_H
#define PROJET_PNJ_H

#include "Position.hpp"
#include "Direction.h"
#include "Map.hpp"
#include "Wave.h"

class PNJ{

private:

	int healthPoints;
	int direction;
	int movementSpeed;
	Position position;

public:

	PNJ();

    PNJ(Position position, int healthPoints, int movementSpeed);

    ~PNJ() = default;

	void advance(Map& map);

	int getHealthPoints() const;

	void receiveDamage(int damageAmount);

	int getMovementSpeed() const;

	void setMovementSpeed(int newMovementSpeed);

    void receiveMovementPenalty(int speedReduction);

	Position getPosition() const;

	void setPosition(Position position);

	bool can_go_forward(int wave_id, Position &current_pos);

	bool can_go_left(int wave_id, Position &current_pos, Position &last_pos);

	bool can_go_right(int wave_id, Position &current_pos, Position &last_pos);

	Direction get_forward_direction(int wave_id);

	Direction get_right_direction(int wave_id);

	Direction get_left_direction(int wave_id);

};

#endif // PROJET_PNJ_H
