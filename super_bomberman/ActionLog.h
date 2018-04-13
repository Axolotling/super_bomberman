#pragma once
#include <list>
#include <string>
//#include "LocalPlayer.h"

class ActionLog
{
	int playerid;
	//LocalPlayer *local_player;
	int current_pos_x;
	int current_pos_y;
public:
	float get_current_pos_x() const
	{
		return static_cast<float>(current_pos_x);
	}

	void set_current_pos_x(float current_pos_x)
	{
		this->current_pos_x = static_cast<int>(current_pos_x);
	}

	float get_current_pos_y() const
	{
		return static_cast<float>(current_pos_y);
	}

	void set_current_pos_y(float current_pos_y)
	{
		this->current_pos_y = static_cast<int>(current_pos_y);
	}

	enum Communicate
	{
		key_up_pressed = 10, // enum zaczyna od 10
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
		kill_player
	};
	

	std::string create_final_message_from_list();

	std::string communicate_to_string(Communicate communicate);

	std::list<std::string> communicates_to_send;

	bool is_empty()
	{
		return communicates_to_send.empty();
	}

	void clear_communicates_to_send();

	void push_communicate(std::string single_communicate);
	
	ActionLog(int playerId);
	//ActionLog(LocalPlayer* player);
	~ActionLog();
};

