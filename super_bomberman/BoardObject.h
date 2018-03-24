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
#include "Displayable.h"
#include <SFML/Graphics/RenderWindow.hpp>

#define epsilon 0.1

class BombermanGame;

// Klasa abstrakcyjna, która opisuje obiekt który może zostać umieszczony na planszy gry
class BoardObject : public Displayable
{
// Public definitions
	///none
// Private fields

// Protected fields
protected:
	
// Public fields
public:
	sf::Drawable *drawable;
	// Gdzie na planszy znajduje się obiekt
	int board_x, board_y;
	bool can_be_broken;
	bool can_be_collided;
	bool requires_update;
	BombermanGame* bomberman_game;
	sf::Texture *texture = new sf::Texture;

// Constructors and destructors
	BoardObject(BombermanGame* bomberman_game, const int& board_x, const int& board_y, bool can_be_broken = true,
	            bool can_be_collided = true);;

	virtual ~BoardObject();;

// Private methods
	///none
// Public methods
	virtual sf::Sprite* get_graphical_representation();

	void update() override;

	void display(sf::RenderWindow* window) override;

	enum collision
	{
		top,
		right,
		bottom,
		left,
		none
	};

	std::set<collision> collider(double x, double y, double w, double h);
};


#endif
