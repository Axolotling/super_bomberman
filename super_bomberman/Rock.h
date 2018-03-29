#pragma once
#include "BoardObject.h"
class Rock :
	public BoardObject
{
public:
	Rock(BombermanGame *bomberman_game, const int &board_x, const int &board_y);
	~Rock();
};

