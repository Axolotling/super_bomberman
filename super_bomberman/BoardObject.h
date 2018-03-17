#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H
#include <SFML/Graphics/Drawable.hpp>
#include <list>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <iostream>


class BombermanGame;

// Klasa abstrakcyjna, która opisuje obiekt który może zostać umieszczony na planszy gry
class BoardObject
{
// Public definitions
	///none
// Private fields

// Protected fields
protected:
	
// Public fields
public:
	// Gdzie na planszy znajduje się obiekt
	int board_x, board_y;
	bool can_be_broken;
	bool can_be_collided;
	BombermanGame* bomberman_game;

// Constructors and destructors
	BoardObject(BombermanGame* bomberman_game, const int &board_x, const int &board_y, bool can_be_broken = true, bool can_be_collided = true) :
	board_x(board_x), 
	board_y(board_y),	
	can_be_broken(can_be_broken),
	can_be_collided(can_be_collided),
	bomberman_game(bomberman_game) {};
	
	virtual ~BoardObject(){};

// Private methods
	///none
// Public methods
	virtual sf::Sprite* get_graphical_representation()
	{
		sf::Sprite* sprite = new sf::Sprite;
		//sprite->setTextureRect(sf::IntRect(1, 1, 1, 1));
		sf::Texture *texture = new sf::Texture;

		if (!texture->loadFromFile("question.png"))
		{
			std::cout << "Grafika obiektu się nie załadowała";
		}
		
		sprite->setTexture(*texture);
		sprite->setTextureRect(sf::IntRect(0, 0,texture->getSize().x,texture->getSize().y));

		return sprite;
	}
};
#endif
