#include "Bomb.h"
#include "Board.h"

Bomb::Bomb(Board* board, const double& board_x, const double& board_y): BoardObject(board, board_x, board_y, false, false)
{
	std::cout << "Created Bomb Object" << std::endl;
	if (!texture->loadFromFile("bomb.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTexture(*texture);
	time_to_go_off = 0.1;
}

Bomb::~Bomb()
{
}

void Bomb::update(sf::Time delta_time)
{
	BoardObject::update(delta_time);
	time_to_go_off -= delta_time.asSeconds();
	if (time_to_go_off <= 0)
	{		
		BoardObject* board_object = board->get_object({ board_x + 1,board_y });
		if (board_object)	board_object->destroy();
		board_object = board->get_object({ board_x - 1,board_y });
		if (board_object)	board_object->destroy();
		board_object = board->get_object({ board_x,board_y + 1 });
		if (board_object)	board_object->destroy();
		board_object = board->get_object({ board_x ,board_y - 1 });
		if (board_object)	board_object->destroy();
		
		destroy_hard();
	}
}
