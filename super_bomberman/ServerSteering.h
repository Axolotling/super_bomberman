#ifndef SERVERSTEERING_H
#define SERVERSTEERING_H

#include "Steering.h"
#include <SFML/Window/Keyboard.hpp>
#include <list>
#include "ActionLog.h"

class ServerSteering : public Steering
{
	//ActionLog *action_log;

	int playerid;
public:

	void ServerSteering::parse_message(std::string recieved_message)
	{
		std::string temp = recieved_message.substr(0, 1);
		int id = atoi(temp.data());
		if (id == playerid)
		{
			while (true)
			{
				int i = 1;
				cout << "hehe " << endl;
				//if (recieved_message[i] == ';')
				
			}
		}
		
	}


	std::list<Action> determine_action() override
	{
		std::list<Action> actions;
		if (get_was_left_key_pressed())//sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			actions.push_front(GO_LEFT);
		}
		if (get_was_right_key_pressed())//sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			actions.push_front(GO_RIGHT);
		}
		if (get_was_up_key_pressed())//sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			actions.push_front(GO_UP);
		}
		if (get_was_down_key_pressed())//sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			actions.push_front(GO_DOWN);
		}
		if (false)//sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			actions.push_front(BOMB);
		}


		if (actions.empty())
		{
			actions.push_front(NONE);
		}
		return actions;
	};


	ServerSteering(int playerid) : playerid(playerid)
	{
		//this->action_log = action_log;
	};
	~ServerSteering() {};
};

#endif