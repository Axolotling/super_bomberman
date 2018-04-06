#pragma once
#include "Player.h"

class LocalPlayer : public Player
{
public:
	LocalPlayer(Board* board, const double& board_x, const double& board_y) : Player(board, board_x, board_y)
	{
		delete steering;
		steering = new ArrowsKeyboardSteering;
	}
	
};

