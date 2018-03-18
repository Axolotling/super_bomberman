#include "BombermanGame.h"
#include "Player.h"
#include "Steering.h"
#include "KeyboardSteering.h"
#include "Board.h"
#include <iostream>
#include <SFML/System/Clock.hpp>
#include "Crate.h"
#include <Windows.h>
Player* BombermanGame::add_player(int x, int y)
{
	Player* new_player = new Player(this, x+1, y+1);
	players.push_front(new_player);
	this->board->set_object({x,y},new_player); //dodajemy obiekt gracza na pozycje x,y (BR)
	return new_player;
}

//<<<<<<< HEAD

//BombermanGame::BombermanGame(const int& board_width, const int& board_height): board_width(board_width), board_height(board_height)
//=======
BombermanGame::BombermanGame()
//>>>>>>> dcf9718d0f66ec0b7934243d2076119288088ee1
{
	this->board = new Board();
	local_player = add_player(0, 0);

	board->set_object({ 6,6 }, new Crate(this, 6, 6));

	board->set_object({ 8,6 }, new Crate(this, 8, 6));
}

// note that friction and speed should be related to the same time period
double BombermanGame::apply_friction_to_speed(const double & friction, double speed)
{
	if (speed < friction && speed > -friction)
	{
		 speed = 0;
	}
	else
	{
		if (speed > 0) speed -= friction;
		if (speed < 0) speed += friction;
	}
	return speed;
}

void BombermanGame::loop()
{
	
	sf::Clock clock;
	// game ticks per second
	const double tickrate = 60;

	double milliseconds_between_ticks = 1000 / tickrate;
	
	std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;

	Steering* steering = new KeyboardSteering;

	int time_of_last_tick = 0;

	double a_seconds = 0.4;
	double a_ticks = a_seconds / tickrate;

	double friction_seconds = 0.4;
	double friction_ticks = friction_seconds / tickrate;

	double max_v_fields_per_second = 6;
	double max_v_fields_per_tick = max_v_fields_per_second / tickrate;

	while (true)
	{
		bool tick = false;
		Sleep(milliseconds_between_ticks / 4);
		/*
		 * velocity = blocks per second
		 */

		if (clock.getElapsedTime().asMilliseconds() >= time_of_last_tick + milliseconds_between_ticks)
		{
			tick = true;
			time_of_last_tick = time_of_last_tick + int(milliseconds_between_ticks);
		}

		

		if (tick)
		{
			if (local_player->board_x < board->get_map_size().first-1)
			{
				//local_player->move_player(1, 0);
				bool pressed_up_or_down = false;
				bool pressed_left_or_right = false;

				for (auto action : steering->determine_action()) {


					switch (action)
					{
					case Steering::GO_UP:
						pressed_up_or_down = true;
						local_player->y_velocity += -a_ticks;
						if (local_player->y_velocity < -max_v_fields_per_tick) local_player->y_velocity = -max_v_fields_per_tick;						
						break;
					case Steering::GO_DOWN:
						pressed_up_or_down = true;
						local_player->y_velocity += a_ticks;
						if (local_player->y_velocity > max_v_fields_per_tick) local_player->y_velocity = max_v_fields_per_tick;
						break;
					case Steering::GO_LEFT:
						pressed_left_or_right = true;
						local_player->x_velocity += -a_ticks;
						if (local_player->x_velocity < -max_v_fields_per_tick) local_player->x_velocity = -max_v_fields_per_tick;
						break;
					case Steering::GO_RIGHT:
						pressed_left_or_right = true;
						local_player->x_velocity += a_ticks;
						if (local_player->x_velocity > max_v_fields_per_tick) local_player->x_velocity = max_v_fields_per_tick;
						break;
					case Steering::NONE:
						break;
					default:
						break;
					}

				}
				if (!pressed_left_or_right)				
					local_player->x_velocity = apply_friction_to_speed(friction_ticks, local_player->x_velocity);
				
				if (!pressed_up_or_down)				
					local_player->y_velocity = apply_friction_to_speed(friction_ticks, local_player->y_velocity);
			}
			local_player->move_player(local_player->x_velocity, local_player->y_velocity);			
		}
	}
}
