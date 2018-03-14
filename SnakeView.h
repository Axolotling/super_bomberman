#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include "View.h"
#include "SFML/Graphics.hpp"
#include "Snake.h"
class SnakeView : public View
{
	Snake *snake_;	
	double basic_gridbase_ = 10;
	
public:
	SnakeView(Snake* snake) : snake_(snake) {}
	~SnakeView() {};
	
	//void update(double offset_x, double offset_y, double scale = 1.0, double background_width = 0.0, double background_height = 0.0, sf::Color color = sf::Color::Black) override
	
	void update(double x, double y, double width = 0.0, double height = 0.0, double inner_offset_x = 0.0, double inner_offset_y = 0.0, double scale = 1.0, sf::Color color = sf::Color::Transparent) override
	{
		delete_drawables();
		const double gridbase = basic_gridbase_ * scale;
		for (auto i : snake_->body)
		{
			sf::RectangleShape *rectangle = new sf::RectangleShape(sf::Vector2f(gridbase, gridbase));
			rectangle->setFillColor(sf::Color::White);
			rectangle->setPosition(i->x*gridbase + x + inner_offset_x , i->y*gridbase + y + inner_offset_y);
			drawables.push_front(rectangle);
		}
		sf::RectangleShape *rectangle = new sf::RectangleShape(sf::Vector2f(gridbase, gridbase));
		rectangle->setFillColor(sf::Color::Green);
		rectangle->setPosition(snake_->food_x*gridbase + x + inner_offset_x, snake_->food_y*gridbase + y + inner_offset_y);
		drawables.push_front(rectangle);
		
		View::create_background(x, y, width, height, color);
		//View::update(offset_x, offset_y, scale, width, height, color);
	}
};

#endif