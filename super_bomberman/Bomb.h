#pragma once
#include "BoardObject.h"



class Bomb : public BoardObject
{
	double time_to_go_off;
public:
	Bomb(Board* board, const double& board_x, const double& board_y);;
	~Bomb();;

	void update(sf::Time delta_time) override;;
};

