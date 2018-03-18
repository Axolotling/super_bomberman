#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H
#include <SFML/Graphics/Drawable.hpp>
#include <list>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <iostream>
#include <set>

#define epsilon 0.1

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
	sf::Texture *texture = new sf::Texture;

// Constructors and destructors
	BoardObject(BombermanGame* bomberman_game, const int &board_x, const int &board_y, bool can_be_broken = true, bool can_be_collided = true) :
	board_x(board_x), 
	board_y(board_y),	
	can_be_broken(can_be_broken),
	can_be_collided(can_be_collided),
	bomberman_game(bomberman_game)
	{
		
		if (!texture->loadFromFile("question.png"))
		{
			std::cout << "Grafika obiektu się nie załadowała";
		}

	};
	


	virtual ~BoardObject(){};

// Private methods
	///none
// Public methods
	virtual sf::Sprite* get_graphical_representation()
	{
		sf::Sprite* sprite = new sf::Sprite;
		//sprite->setTextureRect(sf::IntRect(1, 1, 1, 1));
		

		
		
		sprite->setTexture(*texture);
		sprite->setTextureRect(sf::IntRect(0, 0,texture->getSize().x,texture->getSize().y));

		return sprite;
	}

	enum collision
	{
		top,
		right,
		bottom,
		left,
		none
	};



	std::set<collision> collider(double x, double y, double w, double h)
	{
		if (can_be_collided)
		{
			std::set<collision> collisions;

			if (x + w - epsilon > board_x && x + epsilon < board_x + 1)
				if (y > board_y) collisions.insert(top);
				else collisions.insert(bottom);
			

			if (y + h - epsilon > board_y && y + epsilon < board_y + 1) 
				if(x < board_x) collisions.insert(right);
				else collisions.insert(left);		

			
			return collisions;
		}

	}
	
};
#endif
