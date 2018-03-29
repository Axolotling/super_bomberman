#pragma once
#include "BoardObject.h"


class Crate : public BoardObject
{
public:
	Crate(Board *board, const double &board_x, const double &board_y) : BoardObject(board, board_x, board_y, true, true)
	{
		//std::cout << "Created Crate Object" << std::endl;
		if (!texture->loadFromFile("crate.png"))
		{
			std::cout << "Grafika obiektu siê nie za³adowa³a";
		}
		sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
		sprite->setTexture(*texture);
		
	};
	~Crate();
};


