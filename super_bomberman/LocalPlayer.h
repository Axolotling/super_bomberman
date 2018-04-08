#pragma once
#include "Player.h"

class LocalPlayer : public Player
{
	
	
public:
	ActionLog * action_log;

	LocalPlayer(Board* board, const double& board_x, const double& board_y, int id, ActionLog* action_log, Communicator *communicator) : Player(board, board_x, board_y, id, action_log ,communicator)
	{
		this->action_log = action_log;
		delete steering;
		steering = new ArrowsKeyboardSteering(action_log);
	}
	
};

