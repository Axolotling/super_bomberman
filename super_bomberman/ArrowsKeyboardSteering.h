#ifndef ARROWSKEYBOARDSTEERING_H
#define ARROWSKEYBOARDSTEERING_H

#include "Steering.h"
#include <SFML/Window/Keyboard.hpp>
#include <list>
#include "ActionLog.h"
#include "Communicator.h"

class ArrowsKeyboardSteering : public Steering
{
	ActionLog *action_log;

public:

	

	std::list<Action> determine_action() override
	{
		std::list<Action> actions;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (get_was_left_key_pressed() == false)
			{
				//add communicate
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_left_pressed));			
				set_was_left_key_pressed(true);
			}
			actions.push_front(GO_LEFT);
		}
		else
		{
			if (get_was_left_key_pressed() == true)
			{
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_left_released));
			}
			set_was_left_key_pressed(false);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (get_was_right_key_pressed() == false)
			{
				//add communicate
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_right_pressed));
				set_was_right_key_pressed(true);
			}
			actions.push_front(GO_RIGHT);
		}
		else
		{
			if (get_was_right_key_pressed() == true)
			{
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_right_released));
			}
			set_was_right_key_pressed(false);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (get_was_up_key_pressed() == false)
			{
				//add communicate
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_up_pressed));
				set_was_up_key_pressed(true);
			}
			actions.push_front(GO_UP);
		}
		else
		{
			if (get_was_up_key_pressed() == true)
			{
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_up_released));
			}
			set_was_up_key_pressed(false);
		}		


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (get_was_down_key_pressed() == false)
			{
				//add communicate
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_down_pressed));
				set_was_down_key_pressed(true);
			}
			actions.push_front(GO_DOWN);
		}
		else
		{
			if (get_was_down_key_pressed() == true)
			{
				action_log->push_communicate(action_log->communicate_to_string(ActionLog::key_down_released));
			}
			set_was_down_key_pressed(false);
		}
		


		////////do dokonczenie wysylanie komunikatow w zaleznosci od pozosta³ych zdarzeñ
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			action_log->push_communicate(action_log->communicate_to_string(ActionLog::put_bomb));
			//actions.push_front(BOMB);
		}


		if (actions.empty())
		{
			actions.push_front(NONE);
		}
		return actions;
	};

	ArrowsKeyboardSteering(ActionLog *action_log)
	{
		this->action_log = action_log;
	};
	~ArrowsKeyboardSteering() {};
};

#endif