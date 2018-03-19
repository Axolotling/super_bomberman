#pragma once
#include "BoardObject.h"
class Rock :
	public BoardObject
{
public:
	Rock(BombermanGame *bomberman_game, const double &board_x, const double &board_y);
	~Rock();
};

