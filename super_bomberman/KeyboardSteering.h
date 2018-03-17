#ifndef KEYBOARDSTEERING_H
#define KEYBOARDSTEERING_H

#include "Steering.h"
#include <SFML/Window/Keyboard.hpp>

class KeyboardSteering : public Steering
{
public:
	std::list<Action> determine_action() override
	{
		std::list<Action> actions;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			actions.push_front(GO_LEFT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			actions.push_front(GO_RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			actions.push_front(GO_UP);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			actions.push_front(GO_DOWN);
		}

		if (actions.empty())
		{
			actions.push_front(NONE);
		}
		return actions;
	};

	KeyboardSteering() {};
	~KeyboardSteering() {};
};

#endif