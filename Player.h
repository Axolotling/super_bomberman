#ifndef PLAYER_H
#define PLAYER_H


#include "BoardObject.h"


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
	double x_velocity, y_velocity;
	void move_player(double x, double y)
	{
	
		board_x += x;
		board_y += y;

	}
// Public fields
	Orientation orientation;

// Constructors and destructors
	Player(BombermanGame *const bomberman_game, const int &board_x, const int &board_y) : BoardObject(bomberman_game, board_x, board_y, true, true)
	{
		

		orientation = north;
		x_velocity = 0;
		y_velocity = 0;	
	}


// Private methods
// Public methods
};

#endif