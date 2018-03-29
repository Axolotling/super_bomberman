#pragma once
#include "BoardObject.h"
#include "KeyboardSteering.h"
#include <iostream>



class Player : public BoardObject
{
public:
	Player(Board* board, const double& board_x, const double& board_y);;
	~Player();;

	double exact_x;
	double exact_y;
	Board* board;
	double speed_x = 0;
	double speed_y = 0;

	double max_speed = 3;

	double acceleration = 50;

	double friction = 10;

	KeyboardSteering steering;

	void make_speed_smaller_or_equal_max();

	void apply_friction_to_speed(const sf::Time& delta_time);

	bool is_there_collision_on_the_right();

	void update(sf::Time delta_time) override;;

};

