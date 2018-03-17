#ifndef BOMBERMANGAMEVIEW_H
#define BOMBERMANGAMEVIEW_H

#include "View.h"
#include "SFML/Graphics.hpp"
#include "Snake.h"
#include "BombermanGame.h"
#include "Player.h"

class BombermanGameView : public View
{


// Public definitions

// Private fields
private:
	BombermanGame *bomberman_game;

// Public fields
public:
// Constructors and destructors
	BombermanGameView(BombermanGame *bomberman_game) : bomberman_game(bomberman_game) {};
	
	~BombermanGameView() {};

// Private methods
	void create_vertical_grid_lines(double start_x, double start_y, double grid_cell_side, double line_weight = 2.0)
	{
		for (int i = 1; i < bomberman_game->board_width; i++)
		{
			sf::RectangleShape *line = new sf::RectangleShape(sf::Vector2f(line_weight, bomberman_game->board_height * grid_cell_side));
			line->setPosition(start_x + grid_cell_side * i, start_y);
			line->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(line);
		}
	}

	void create_horizontal_grid_lines(double start_x, double start_y, double grid_cell_side, double line_weight = 2.0)
	{
		for (int i = 1; i < bomberman_game->board_height; i++)
		{
			sf::RectangleShape *line = new sf::RectangleShape(sf::Vector2f(bomberman_game->board_width * grid_cell_side, line_weight));
			line->setPosition(start_x, start_y + grid_cell_side * i);
			line->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(line);
		}
	}

	void display_every_object_on_board(double start_x, double start_y, double grid_cell_side)
	{
		for (int x = 0; x < bomberman_game->board_width; x++)
		{
			for (int y = 0; y < bomberman_game->board_height; y++)
			{
				if (bomberman_game->board[x][y] != nullptr)
				{
					sf::Sprite *sprite = bomberman_game->board[x][y]->get_graphical_representation();
					sprite->setScale(grid_cell_side / sprite->getTextureRect().width, grid_cell_side / sprite->getTextureRect().height);

					//sf::CircleShape *sprite = new sf::CircleShape(grid_cell_side / 2);					
					//sprite->setFillColor(sf::Color(40, 40, 200));

					Player* player;
					if (player = dynamic_cast<Player*>(bomberman_game->board[x][y]))
					{
						sprite->setPosition(start_x + grid_cell_side * player->exact_x, start_y + grid_cell_side * player->exact_y);
					}
					else
					{
						sprite->setPosition(start_x + grid_cell_side * x, start_y + grid_cell_side * y);
					}

				
					drawables.push_back(sprite);
				}
			}
		}
	};


// Public methods
public:	
	void update(double x, double y, double width = 0.0, double height = 0.0, double inner_offset_x = 0.0, double inner_offset_y = 0.0, double scale = 1.0, sf::Color color = sf::Color::Transparent) override
	{
		delete_drawables();
		const double grid_cell_side = scale;

		create_vertical_grid_lines(x, y, grid_cell_side);		
		create_horizontal_grid_lines(x, y, grid_cell_side);
		display_every_object_on_board(x, y, grid_cell_side);

		//game background
		create_background(x, y, bomberman_game->board_width*grid_cell_side, bomberman_game->board_height*grid_cell_side, sf::Color(200,150,0));
		
		///create_background(x, y, bomberman_game->board_width*gridbase, bomberman_game->board_height*gridbase, color);
	}
};


#endif