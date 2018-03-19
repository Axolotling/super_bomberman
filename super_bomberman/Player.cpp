#include "Player.h"
#include "BombermanGame.h"
#include "Board.h"



void Player::move_player(double x_difference, double y_difference)
{
	requires_update = true;

	int remembered_board_x = board_x, remembered_board_y = board_y;
	int board_width = bomberman_game->board->get_map_size().first;
	int board_height = bomberman_game->board->get_map_size().second;
	//bomberman_game->board[board_x][board_y] = nullptr;
	

	auto a = check_collisions();

	exact_x += x_difference;
	exact_y += y_difference;

	if (a.find(right) != a.end() && x_difference > 0) exact_x -= x_difference;
	else if (a.find(left) != a.end() && x_difference < 0) exact_x -= x_difference;
	
	if (a.find(bottom) != a.end() && y_difference > 0) exact_y -= y_difference;
	else if (a.find(top) != a.end() && y_difference < 0) exact_y -= y_difference;


	


	if (exact_x > board_width - 1) exact_x = board_width - 1.000000001;
	if (exact_x < 0) exact_x = 0;
	if (exact_y < 0) exact_y = 0;
	if (exact_y > board_height - 1) exact_y = board_height - 1;


	/*if (static_cast<int>(exact_x) != remembered_board_x || static_cast<int>(exact_y) != remembered_board_y)
	{
		bomberman_game->board->set_object({remembered_board_x,remembered_board_y},nullptr);
		board_x = static_cast<int>(exact_x);
		board_y = static_cast<int>(exact_y);
		bomberman_game->board->set_object({board_x,board_y},this);
	}*/
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



std::set<BoardObject::collision> Player::check_collisions()
{	
	std::set<collision> set_of_collisions;
	for (int x = exact_x; x < exact_x+1; x++)
	{
		for (int y = exact_y; y < exact_y+1; y++)
		{
			BoardObject *object = bomberman_game->board->get_object({ x,y });
			if (object != nullptr)
			{
				auto collisions = check_collision_with(object);
				set_of_collisions.insert(collisions.begin(), collisions.end());
			}
			
		}
	}

	//set_of_collisions.find(BoardObject::top);



	return set_of_collisions;
//>>>>>>> generating_map
}



std::set<BoardObject::collision> Player::check_collision_with(BoardObject* board_object)
{
	return board_object->collider(exact_x, exact_y, 1, 1);
}