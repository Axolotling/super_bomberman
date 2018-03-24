#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include <SFML/Graphics.hpp>

class Displayable
{	
public:
	virtual void display(sf::RenderWindow *window) = 0;
	virtual void update() = 0;
};

#endif