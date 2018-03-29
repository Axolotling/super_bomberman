#include "Bomb.h"
#include "Board.h"

Bomb::Bomb(Board* board, const double& board_x, const double& board_y): BoardObject(
	board, board_x, board_y, false, true)
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
	picture_slice_width -= delta_time.asSeconds();
	picture_slice_height -= delta_time.asSeconds();
	if (picture_slice_width <= 0 || picture_slice_height <= 0)
	{
		//board->set_object({board_x, board_y}, nullptr);
		cout << "Bomba znika" << endl;
	//	delete this;
	}
	BoardObject::update(delta_time);
}
