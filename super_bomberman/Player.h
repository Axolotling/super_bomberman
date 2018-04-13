#pragma once
#include "BoardObject.h"
#include <iostream>
#include "ArrowsKeyboardSteering.h"


class Player : public BoardObject
{
	int id;
	Communicator *communicator;
	ActionLog *action_log;


public:
	Player(Board* board, const double& board_x, const double& board_y, int id, ActionLog *action_log,Communicator *communicator);
	~Player();

	float exact_x;
	float exact_y;
	float speed_x = 0;
	float speed_y = 0;

	void setId(int value)
	{
		id = value;
	}

	int getId()
	{
		return id;
	}

	float max_speed = 3;

	float acceleration = 50;

	float friction = 10;

	Steering *steering;

	void make_speed_smaller_or_equal_max();

	void apply_friction_to_speed(const sf::Time& delta_time);

	bool is_there_collision_on_the_right();
	bool is_object_on_field(int checked_x, int checked_y);

	bool is_there_collision_on_the_left();

	bool is_there_collision_on_the_top();

	bool is_there_collision_on_the_bottom();

	void update(sf::Time delta_time) override;

};

