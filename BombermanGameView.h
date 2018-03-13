#pragma once
#include "View.h"
#include "SFML/Graphics.hpp"
#include "Snake.h"
#include "BombermanGame.h"

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
	void create_vertical_lines(double start_x, double start_y, double grid_cell_side, double line_weight = 2.0)
	{
		for (int i = 1; i < bomberman_game->board_width; i++)
		{
			sf::RectangleShape *stripe = new sf::RectangleShape(sf::Vector2f(line_weight, bomberman_game->board_height * grid_cell_side));
			stripe->setPosition(start_x + grid_cell_side * i, start_y);
			stripe->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(stripe);
		}
	}

	void create_horizontal_lines(double start_x, double start_y, double grid_cell_side, double line_weight = 2.0)
	{
		for (int i = 1; i < bomberman_game->board_height; i++)
		{
			sf::RectangleShape *stripe = new sf::RectangleShape(sf::Vector2f(bomberman_game->board_width * grid_cell_side, line_weight));
			stripe->setPosition(start_x, start_y + grid_cell_side * i);
			stripe->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(stripe);
		}
	}

// Public methods
public:	
	void update(double x, double y, double width = 0.0, double height = 0.0, double inner_offset_x = 0.0, double inner_offset_y = 0.0, double scale = 1.0, sf::Color color = sf::Color::Transparent) override
	{
		delete_drawables();
		const double grid_cell_side = scale;

		create_vertical_lines(x, y, grid_cell_side);
		
		create_horizontal_lines(x, y, grid_cell_side);

		//game background
		create_background(x, y, bomberman_game->board_width*grid_cell_side, bomberman_game->board_height*grid_cell_side, sf::Color(200,150,0));
		
		///create_background(x, y, bomberman_game->board_width*gridbase, bomberman_game->board_height*gridbase, color);
	}
};
