#pragma once
#include <list>
#include <string>

class ActionLog
{
	int playerid;
public:
	enum Communicate
	{
		key_up_pressed,
		key_down_pressed,
		key_left_pressed,
		key_right_pressed,
		key_up_released,
		key_down_released,
		key_left_released,
		key_right_released,
		put_bomb,
		erase_crate,
		get_bonus,
		kill_player//,
		//start_rozkaz,
		//end_rozkaz
	};

	void send_communicates_to_server();

	std::string concatenate_communicates_from_list();

	std::string communicate_to_string(Communicate communicate);

	std::list<std::string> communicates_to_send;


	void clear_communicates_to_send();

	void push_communicate(std::string single_communicate);
	
	ActionLog(int playerid);
	~ActionLog();
};

