#ifndef WSADKEYBOARDSTEERING_H
#define WSADKEYBOARDSTEERING_H

#include "Steering.h"
#include <SFML/Window/Keyboard.hpp>
#include <list>

class WsadKeyboardSteering : public Steering
{
public:
	std::list<Action> determine_action() override
	{
		std::list<Action> actions;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			actions.push_front(GO_LEFT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			actions.push_front(GO_RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			actions.push_front(GO_UP);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			actions.push_front(GO_DOWN);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			actions.push_front(BOMB);
		}


		if (actions.empty())
		{
			actions.push_front(NONE);
		}
		return actions;
	};

	WsadKeyboardSteering() {};
	~WsadKeyboardSteering() {};
};

#endif