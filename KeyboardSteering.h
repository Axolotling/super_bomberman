#ifndef KEYBOARDSTEERING_H
#define KEYBOARDSTEERING_H

#include "Steering.h"
#include <SFML/Window/Keyboard.hpp>

class KeyboardSteering : public Steering
{
public:
	Action determine_action() override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			return GO_LEFT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			return GO_RIGHT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			return GO_UP;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			return GO_DOWN;
		}
		return NONE;
	};

	KeyboardSteering() {};
	~KeyboardSteering() {};
};

#endif