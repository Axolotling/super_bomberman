#pragma once

#include "Displayable.h"
#include <set>
#include "Board.h"



#define epsilon 0.1
// Klasa abstrakcyjna, która opisuje obiekt który mo¿e zostaæ umieszczony na planszy gry
class BoardObject : public Displayable
{
	// Public fields
public:
	sf::Drawable *drawable;
	// Gdzie na planszy znajduje siê obiekt
	int board_x, board_y;
	bool can_be_broken;
	bool can_be_collided;
	Board *board;
	int picture_slice_width;
	int picture_slice_height;
	double grid_cell_side = 40;
#define psw picture_slice_width
#define psh picture_slice_height
	sf::Texture *texture = new sf::Texture;

	// Constructors and destructors
	BoardObject(Board* board, const int& board_x, const int& board_y, bool can_be_broken = true,
	            bool can_be_collided = true);

	~BoardObject();;


	void update(sf::Time delta_time) override;;

	void display(sf::RenderWindow* window) override;;

	enum collision
	{
		top,
		right,
		bottom,
		left,
		none
	};

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
};


