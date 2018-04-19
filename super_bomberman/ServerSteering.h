#ifndef SERVERSTEERING_H
#define SERVERSTEERING_H

#include "Steering.h"
#include <SFML/Window/Keyboard.hpp>
#include <list>
#include "ActionLog.h"
#include "Board.h"
#include "Bomb.h"

class ServerSteering : public Steering
{
	//ActionLog *action_log;

	int playerid;
	Board *board;
public:

	void ServerSteering::parse_message()
	{

		while (!board->get_communicator()->is_message_list_empty()) {
			std::string recieved_message = board->get_communicator()->pop_first_recieved_message();
			std::string temp = recieved_message.substr(0, 1);
			int id = atoi(temp.data());
			if (id > this->board->get_communicator()->get_current_player_number()) this->board->get_communicator()->set_current_player_number(id);
			if (id == playerid)
			{
				cout << "Parsujemy o taka wiadomosc: " << recieved_message << ", wiemy ze id playera to " << id << endl;
				int parsed_int;

				bool d, u, l, r;
				d=u=l=r=0;
				for (int i = 2; i < recieved_message.length();) {

					std::string parsed_string = recieved_message.substr(i, i + 2);

					parsed_int = atoi(parsed_string.data());

					if (parsed_int < 10 && parsed_string[i+1]=='_') {
					cout << "Blednie odebrany rozkaz" << endl;
					//
					string tmp1 = recieved_message.substr(i, recieved_message.length()-i);
					board->get_communicator()->push_message(tmp1);
					break;
					}

					cout << "parsowany rozkaz ma nr: " << parsed_int << endl;

					i += 3;
					switch (static_cast<ActionLog::Communicate>(parsed_int)) {
					case ActionLog::key_up_pressed:
						set_was_up_key_pressed(true);
						u = 1;
						break;
					case ActionLog::key_down_pressed:
						set_was_down_key_pressed(true);
						d = 1;
						break;
					case ActionLog::key_left_pressed:
						set_was_left_key_pressed(true);
						l = 1;
						break;
					case ActionLog::key_right_pressed:
						set_was_right_key_pressed(true);
						r = 1;
						break;
					case ActionLog::key_up_released:
						set_was_up_key_pressed(false);
						break;
					case ActionLog::key_down_released:
						set_was_down_key_pressed(false);
						break;
					case ActionLog::key_left_released:
						set_was_left_key_pressed(false);
						break;
					case ActionLog::key_right_released:
						set_was_right_key_pressed(false);
						break;
					case ActionLog::put_bomb: {
						int j = i;
						cout << "Wykryto bombe do postawienia" << endl;
						while (recieved_message[j] != ';') j++;
						parsed_string = recieved_message.substr(i, j);
						parsed_int = atoi(parsed_string.data());
						//uzywamy x
						int x = parsed_int;
						j++;
						i = j;
						while (recieved_message[j] != ';') j++;

						parsed_string = recieved_message.substr(i, j);
						parsed_int = atoi(parsed_string.data());
						int y = parsed_int;
						i = j;
						i++;
						if (board->get_object({ x, y }) == nullptr)
						{
							board->set_object({ x, y }, new Bomb(board, x, y));
						}
						break;
					}
					case ActionLog::erase_crate: break;
					case ActionLog::get_bonus: break;
					case ActionLog::kill_player: break;
					case ActionLog::update_position: {
						int j = i;
						float parsed_float;
						while (recieved_message[j] != ';') j++;
						parsed_string = recieved_message.substr(i, j);
						parsed_float = atof(parsed_string.data());
						//uzywamy x
						float x = parsed_float;
						j++;
						i = j;
						while (recieved_message[j] != ';') j++;

						parsed_string = recieved_message.substr(i, j);
						parsed_int = atof(parsed_string.data());
						float y = parsed_float;
						i = j;
						i++;
						for (Player *p : board->get_players_list())
						{
							if (p->getId() == id) p->set_xy(x, y);
						}
						
						break;
					}
					default:;
					}				


				}
				if (!u) set_was_up_key_pressed(false);
				if (!d) set_was_down_key_pressed(false);
				if (!l) set_was_left_key_pressed(false);
				if (!r) set_was_right_key_pressed(false);

				
			}
			else
			{
				board->get_communicator()->push_message(recieved_message);
				break;
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


	ServerSteering(int playerid, Board *board) : playerid(playerid), board(board)
	{
		//this->action_log = action_log;
	};
	~ServerSteering() {};
};

#endif