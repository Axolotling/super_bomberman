#pragma once
#include "BoardObject.h"
#include <iostream>
#include "ArrowsKeyboardSteering.h"


class Player : public BoardObject
{
public:
	Player(Board* board, const double& board_x, const double& board_y);;
	~Player();;

	double exact_x;
	double exact_y;
	double speed_x = 0;
	double speed_y = 0;

	double max_speed = 3;

	double acceleration = 50;

	double friction = 10;

	Steering *steering;

	void make_speed_smaller_or_equal_max();

	void apply_friction_to_speed(const sf::Time& delta_time);

	bool is_there_collision_on_the_right();
	bool is_object_on_field(int checked_x, int checked_y);

	bool is_there_collision_on_the_left();

	bool is_there_collision_on_the_top();

	bool is_there_collision_on_the_bottom();

	void update(sf::Time delta_time) override;;

};

