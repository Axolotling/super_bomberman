#include "BoardObject.h"

BoardObject::BoardObject(BombermanGame* bomberman_game, const int& board_x, const int& board_y,
	bool can_be_broken, bool can_be_collided) :
	board_x(board_x),
	board_y(board_y),
	can_be_broken(can_be_broken),
	can_be_collided(can_be_collided),
	bomberman_game(bomberman_game)
{
	if (!texture->loadFromFile("question.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}
	requires_update = true;
	drawable = new sf::Sprite;

	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTexture(*texture);

}

BoardObject::~BoardObject()
{
}

sf::Sprite* BoardObject::get_graphical_representation()
{
	sf::Sprite* sprite = new sf::Sprite;

	if (!texture->loadFromFile("question.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}

	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));

	return sprite;
}

void BoardObject::update()
{
	


	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);

	sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	sprite->setPosition(board_x * 27, board_y * 27);
	sprite->setScale(0.1,0.1);
	drawable = sprite;
}

void BoardObject::display(sf::RenderWindow* window)
{
	if (drawable != nullptr)
	{
		window->draw(*drawable);
	}
}

std::set<BoardObject::collision> BoardObject::collider(double x, double y, double w, double h)
{
	if (can_be_collided)
	{
		std::set<collision> collisions;

		if (x + w - epsilon > board_x && x + epsilon < board_x + 1)
			if (y > board_y) collisions.insert(top);
			else collisions.insert(bottom);

		if (y + h - epsilon > board_y && y + epsilon < board_y + 1)
			if (x < board_x) collisions.insert(right);
			else collisions.insert(left);

		return collisions;
	}
}