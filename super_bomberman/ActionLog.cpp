#include "ActionLog.h"
#include <iostream>


std::string ActionLog::create_final_message_from_list()
{
	std::cout << "created final communicate: ";
	std::string result;
	result = std::to_string(playerid); //+getPlayerId
	result += ";";
	for (std::string one_string : communicates_to_send)
	{
		result += one_string;
	}
	std::cout << result << std::endl;
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
		return std::to_string(communicate) + ";" + std::to_string(static_cast<int>(get_current_pos_x()+0.5))+';'+ std::to_string(static_cast<int>(get_current_pos_y()+0.5))+';';
	case get_bonus:
		return std::to_string(communicate) + ";" + std::to_string(static_cast<int>(get_current_pos_x()+0.5)) + ';' + std::to_string(static_cast<int>(get_current_pos_y()+0.5)) + ';';
	case kill_player:
		break;
	case update_position:
		return std::to_string(communicate) + ";" + std::to_string(get_current_pos_x() + 0.5) + ';' + std::to_string(get_current_pos_y() + 0.5) + ';';
	default: ;
	}
}

//ActionLog::ActionLog(LocalPlayer *player)
//{
//	local_player = player;
//	this->playerid = player->getId();
//}

ActionLog::ActionLog(int playerId)
{
	//local_player = player;
	this->playerid = playerId; //player->getId();
}


ActionLog::~ActionLog()
{
}
