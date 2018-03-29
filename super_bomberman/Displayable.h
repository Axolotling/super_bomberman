#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include <SFML/Graphics.hpp>

class Displayable
{
public:
	virtual void display(sf::RenderWindow *window) = 0;
	virtual void update(sf::Time delta_time) = 0;
};

#endif