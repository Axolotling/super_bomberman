#include "BombermanGame.h"
#include "Player.h"
#include "Steering.h"
#include "KeyboardSteering.h"
#include <iostream>

Player* BombermanGame::add_player(int x, int y)
{
	Player* new_player = new Player(this, x, y);
	players.push_front(new_player);
	board[x][y] = new_player;
	return new_player;
}

BombermanGame::BombermanGame(const int& board_width, const int& board_height): board_width(board_width), board_height(board_height)
{
	board = new BoardObject**[board_width];
	for (int i = 0; i < board_width; i++)
	{
		board[i] = new BoardObject*[board_height];
		for (int j = 0; j < board_height; j++)
		{
			board[i][j] = nullptr;
		}
	}
	local_player = add_player(0, 0);
}

void BombermanGame::loop()
{
	Steering* steering = new KeyboardSteering;

	while(true)
	{
		if (local_player->board_x < board_width - 1)
		{
		//local_player->move_player(1, 0);
			auto action = steering->determine_action();

			switch (action)
			{
			case Steering::GO_DOWN:
				local_player->y_velocity = 1;
				break;

			default:

				break;
			}
		}
		

		local_player->move_player(local_player->x_velocity, local_player->y_velocity);
	}
}
