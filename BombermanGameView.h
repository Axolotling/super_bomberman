#pragma once
#include "View.h"
#include "SFML/Graphics.hpp"
#include "Snake.h"
#include "BombermanGame.h"

class BombermanGameView : public View
{
	BombermanGame *bomberman_game;
	double basic_gridbase_ = 1;

public:
	BombermanGameView(BombermanGame *bomberman_game) : bomberman_game(bomberman_game) {};
	~BombermanGameView() {};

	void update(double x, double y, double width = 0.0, double height = 0.0, double inner_offset_x = 0.0, double inner_offset_y = 0.0, double scale = 1.0, sf::Color color = sf::Color::Transparent) override
	{
		delete_drawables();
		const double gridbase = basic_gridbase_ * scale;

		//vertical stripes
		for (int i = 1; i < bomberman_game->board_width; i++)
		{
			sf::RectangleShape *stripe = new sf::RectangleShape(sf::Vector2f(2, bomberman_game->board_height * gridbase));
			stripe->setPosition(x + gridbase * i, y);
			stripe->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(stripe);
		}

		//horizontal stripes
		for (int i = 1; i < bomberman_game->board_height; i++)
		{
			sf::RectangleShape *stripe = new sf::RectangleShape(sf::Vector2f(bomberman_game->board_width * gridbase, 2));
			stripe->setPosition(x, y + gridbase * i);
			stripe->setFillColor(sf::Color(40, 40, 40));
			drawables.push_back(stripe);
		}

		//game background
		create_background(x, y, bomberman_game->board_width*gridbase, bomberman_game->board_height*gridbase, sf::Color(200,150,0));
		
		//view background
		//create_background(x, y, bomberman_game->board_width*gridbase, bomberman_game->board_height*gridbase, color);

	}
};
