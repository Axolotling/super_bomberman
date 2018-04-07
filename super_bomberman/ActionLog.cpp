#include "ActionLog.h"


void ActionLog::send_communicates_to_server()
{
	std::string whole_communicate;
	whole_communicate += concatenate_communicates_from_list();
}

std::string ActionLog::concatenate_communicates_from_list()
{
	std::string result; //+getPlayerId
	result += ";";
	for (std::string one_string : communicates_to_send)
	{
		result += one_string;
	}
	return result;
}

void ActionLog::clear_communicates_to_send()
{
	communicates_to_send.clear();
}

void ActionLog::push_communicate(std::string single_communicate)
{
	communicates_to_send.push_back(single_communicate);
}

std::string ActionLog::communicate_to_string(Communicate communicate)
{
	switch (communicate)
	{
	case key_up_pressed:
	case key_down_pressed:
	case key_left_pressed:
	case key_right_pressed:
	case key_up_released:
	case key_down_released:
	case key_left_released:
	case key_right_released:
		return std::to_string(communicate) + ";";
		break;
	case put_bomb:
	case erase_crate:
	case get_bonus:
	case kill_player:
	default: ;
	}
}

ActionLog::ActionLog(int playerid)
{
	this->playerid = playerid;
}


ActionLog::~ActionLog()
{
}
