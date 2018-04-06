#pragma once
#include "BoardObject.h"



class Rock : public BoardObject
{
public:
	Rock(Board *board, const double &board_x, const double &board_y) : BoardObject(board, board_x, board_y, false, true)
	{
		//std::cout << "Created Rock Object" << std::endl;
		if (!texture->loadFromFile("rock.png"))
		{
			std::cout << "Grafika obiektu siê nie za³adowa³a";
		}
		sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
		sprite->setTexture(*texture);
		
		

	};
	~Rock() {};
};

