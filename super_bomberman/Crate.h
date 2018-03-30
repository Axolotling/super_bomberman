#pragma once
#include "BoardObject.h"

class Crate : public BoardObject
{
public:
	Crate(Board* board, const double& board_x, const double& board_y);
	double total_time = 0;
	void update(sf::Time delta_time) override;

	~Crate();
};


