#include "Bomb.h"
#include "Board.h"

Bomb::Bomb(Board* board, const double& board_x, const double& board_y): BoardObject(board, board_x, board_y, false, false)
{
	std::cout << "Created Bomb Object" << std::endl;
	/*if (!texture->loadFromFile("rock.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTexture(*texture);*/
}

Bomb::~Bomb()
{
}

void Bomb::update(sf::Time delta_time)
{
	BoardObject::update(delta_time);
	//board->shedule_for_deletion(this);
}
