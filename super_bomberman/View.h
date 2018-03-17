#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <list>
//i->view->update(i->x, i->y, i->width, i->height, i->inner_offset_x, i->inner_offset_y, i->scale, i->background_color);
class View
{
public:	
	std::list<sf::Drawable*> drawables;

	virtual void update(double x, double y, double width = 0.0, double height = 0.0, double inner_offset_x = 0.0 , double inner_offset_y = 0.0, double scale = 1.0, sf::Color color = sf::Color::Transparent) = 0;

	void create_background(float x, float y, float background_width = 0.0, float background_height = 0.0, sf::Color color = sf::Color::Black)
	{
		if (background_width * background_height > 0)
		{
			sf::RectangleShape *background = new sf::RectangleShape(sf::Vector2f(background_width, background_height));
			background->setPosition(x, y);
			background->setFillColor(color);
			drawables.push_front(background);
		}
	}

	void delete_drawables()
	{
		for (auto drawable: drawables)	delete drawable;
		drawables.clear();
	}

	View(){};
	~View()
	{
		delete_drawables();
	};
};

#endif