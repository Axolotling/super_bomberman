#ifndef BOMBERMANGAMEVIEW_H
#define BOMBERMANGAMEVIEW_H

#include "View.h"
#include "SFML/Graphics.hpp"
#include "BombermanGame.h"
#include "Player.h"
#include "Board.h"

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
	void create_vertical_grid_lines(float start_x, float start_y, float grid_cell_side, float line_weight = 2.0)
	{
		for (int i = 1; i < bomberman_game->board->get_map_size().first; i++)
		{
			sf::RectangleShape *line = new sf::RectangleShape(sf::Vector2f(line_weight, bomberman_game->board->get_map_size().second * grid_cell_side));
			line->setPosition(start_x + grid_cell_side * i, start_y);
			line->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(line);
		}
	}

	void create_horizontal_grid_lines(float start_x, float start_y, float grid_cell_side, float line_weight = 2.0)
	{
		for (int i = 1; i < bomberman_game->board->get_map_size().second; i++)
		{
			sf::RectangleShape *line = new sf::RectangleShape(sf::Vector2f(bomberman_game->board->get_map_size().first * grid_cell_side, line_weight));
			line->setPosition(start_x, start_y + grid_cell_side * i);
			line->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(line);
		}
	}

	void display_every_object_on_board(float start_x, float start_y, float grid_cell_side)
	{
		for(auto it=bomberman_game->board->begin();it!=bomberman_game->board->end();it++)
			if (it->second != nullptr)
			{

				sf::Sprite *sprite = it->second->get_graphical_representation();
				sprite->setScale(grid_cell_side / sprite->getTextureRect().width, grid_cell_side / sprite->getTextureRect().height);
				Player* player;
				if (player = dynamic_cast<Player*>(it->second))
					sprite->setPosition(start_x + grid_cell_side * float(player->exact_x), start_y + grid_cell_side * float(player->exact_y));
				else
					sprite->setPosition(start_x + grid_cell_side * it->first.first, start_y + grid_cell_side * it->first.second);
				drawables.push_back(sprite);

			}
	};

// Public methods
public:	
	void update(double x, double y, double width = 0.0, double height = 0.0, double inner_offset_x = 0.0, double inner_offset_y = 0.0, double scale = 1.0, sf::Color color = sf::Color::Transparent) override
	{
		delete_drawables();
		const float grid_cell_side = float(scale);

		create_vertical_grid_lines(float(x), float(y), grid_cell_side);		
		create_horizontal_grid_lines(float(x), float(y), grid_cell_side);
		display_every_object_on_board(float(x), float(y), grid_cell_side);

		//game background
		create_background(float(x), float(y), bomberman_game->board->get_map_size().first*grid_cell_side, bomberman_game->board->get_map_size().second*grid_cell_side, sf::Color(200,150,0));
		
		///create_background(x, y, bomberman_game->board_width*gridbase, bomberman_game->board_height*gridbase, color);
	}
};
#endif