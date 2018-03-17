#pragma once
#include "BoardObject.h"
class Crate :
	public BoardObject
{
public:
	Crate(BombermanGame *bomberman_game, const double &board_x, const double &board_y);
	~Crate();
};

