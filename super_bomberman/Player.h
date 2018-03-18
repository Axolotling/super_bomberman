#ifndef PLAYER_H
#define PLAYER_H


#include "BoardObject.h"
#include <set>


class Player : public BoardObject
{
public:
// Public definitions
	enum Orientation
	{
		north,
		east,
		west,
		south
	};

// Private fields
	double exact_x, exact_y;
	double x_velocity, y_velocity;
	void move_player(double x, double y);
// Public fields
	Orientation orientation;

// Constructors and destructors
	Player(BombermanGame*const bomberman_game, const int& board_x, const int& board_y);

// Private methods
// Public methods
	std::set<collision> check_collision_with(BoardObject* board_object);

	std::set<collision> check_collisions();
};


#endif
