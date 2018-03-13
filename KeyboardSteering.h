#pragma once
#include "Steering.h"
#include <SFML/Window/Keyboard.hpp>

class KeyboardSteering : public Steering
{
public:
	Action determine_direction() override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			return LEFT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			return RIGHT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			return UP;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			return DOWN;
		}
		return NONE;
	};

	KeyboardSteering() {};
	~KeyboardSteering() {};
};
