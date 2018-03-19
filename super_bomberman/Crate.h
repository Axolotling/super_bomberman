#pragma once
#include "BoardObject.h"

class Crate : public BoardObject
{
public:
	Crate(BombermanGame *bomberman_game, const int &board_x, const int &board_y);
	~Crate();
};

