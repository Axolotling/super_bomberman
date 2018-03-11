#pragma once
//#include "BombermanGame.h"
class BombermanGame;

class BoardObject
{
	// Public definitions
	// Private fields
	BombermanGame *const bomberman_game;
	// Public fields
public:
	int board_x;
	int board_y;
	bool can_be_broken;
	bool can_be_collided;
	// Constructors and destructors
	BoardObject(BombermanGame *bomberman_game, const int &board_x, const int &board_y, bool can_be_broken = true, bool can_be_collided = true) :
	bomberman_game(bomberman_game), 
	board_x(board_x), 
	board_y(board_y),
	can_be_broken(can_be_broken),
	can_be_collided(can_be_collided) {};
	~BoardObject() {};
	// Private methods
	// Public methods
};


