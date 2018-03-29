#include "BoardObject.h"
#include "Board.h"

BoardObject::BoardObject(Board* board, const int& board_x, const int& board_y, bool can_be_broken, bool can_be_collided)
{
	//std::cout << "Created BoardObject Object" << std::endl;
	this->board_x = board_x;
	this->board_y = board_y;
	this->can_be_broken = can_be_broken;
	this->can_be_collided = can_be_collided;
	this->board = board;

	if (!texture->loadFromFile("question.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}
	picture_slice_height = 64;
	picture_slice_width = 64;
	drawable = new sf::Sprite;

	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTexture(*texture);
}

BoardObject::~BoardObject()
{
}
void BoardObject::update(sf::Time delta_time)
{
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTextureRect(sf::IntRect(0, 0, psw, psh));
	sprite->setPosition(grid_cell_side * board_x, grid_cell_side * board_y);
	sprite->setScale(grid_cell_side / picture_slice_width, grid_cell_side / picture_slice_height);
	//drawable = sprite;
}

void BoardObject::display(sf::RenderWindow* window)
{
	if (drawable != nullptr)
	{
		window->draw(*drawable);
	}
}