#include "Player.h"
#include "BombermanGame.h"

void Player::move_player(double x_difference, double y_difference)
{
	int remembered_board_x = board_x, remembered_board_y = board_y;
	
	bomberman_game->board[board_x][board_y] = nullptr;


	exact_x += x_difference;
	exact_y += y_difference;

	if (static_cast<int>(exact_x) != remembered_board_x || static_cast<int>(exact_y) != remembered_board_y)
	{
		bomberman_game->board[remembered_board_x][remembered_board_y] = nullptr;
		board_x = static_cast<int>(exact_x);
		board_y = static_cast<int>(exact_y);
	}


	bomberman_game->board[board_x][board_y] = this;
}

Player::Player(BombermanGame* bomberman_game, const int& board_x, const int& board_y) : BoardObject(
	bomberman_game, board_x, board_y, true, true)
{
	orientation = north;
	x_velocity = 0;
	y_velocity = 0;
	exact_x = board_x;
	exact_y = board_y;
}