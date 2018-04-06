#include "Crate.h"
#include "Board.h"


Crate::Crate(Board* board, const double& board_x, const double& board_y): BoardObject(
	board, board_x, board_y, true, true)
{
	//std::cout << "Created Crate Object" << std::endl;
	if (!texture->loadFromFile("crate.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTexture(*texture);
}

void Crate::update(sf::Time delta_time)
{
	BoardObject::update(delta_time);
	total_time += delta_time.asSeconds();
}
