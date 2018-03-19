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

#define epsilon 0.00001

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
	bomberman_game(bomberman_game) {};
	
	virtual ~BoardObject(){};

// Private methods
	///none
// Public methods
	virtual sf::Sprite* get_graphical_representation()
	{
		sf::Sprite* sprite = new sf::Sprite;
		//sprite->setTextureRect(sf::IntRect(1, 1, 1, 1));
		
		
		if (!texture->loadFromFile("brick.png"))
		{
			std::cout << "Grafika obiektu się nie załadowała";
		}
		
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

	//*/
/*	collision collider(double x, double y, double w, double h)
=======
		left,
		none
	};
	*/

	std::set<collision> collider(double x, double y, double w, double h)
//>>>>>>> generating_map
	{
		if (can_be_collided)
		{

			
			//coś
/*<<<<<<< HEAD

			// sprawdź górną kolizję
			if (y >= board_y + 0.5 && y <= board_y + 1) return top;
			// sprawdź prawą kolizję
			if (x + w >= board_x && x + w <= board_x + 0.5) return right;
			// sprawdź dolną kolizję
			if (y + h >= board_y && y + h <= board_y + 0.5) return bottom;
			// sprawdź lewą kolizję
			if (x >= board_x + 0.5 && x <= board_x + 1) return left;

=======
*/			std::set<collision> collisions;

			// sprawdź górną kolizję
			if (y >= board_y + 0.5 && y < board_y + 1) collisions.insert(top);
			else
			// sprawdź prawą kolizję
			if (x + w - epsilon > board_x && x + w <= board_x + 0.5) collisions.insert(right);
			else
			// sprawdź dolną kolizję
			if (y + h > board_y && y + h <= board_y + 0.5) collisions.insert(bottom);
			// sprawdź lewą kolizję
			else
			if (x >= board_x + 0.5 && x - epsilon < board_x + 1) collisions.insert(left);
//>>>>>>> generating_map

			return collisions;
		}
	}
};
#endif
