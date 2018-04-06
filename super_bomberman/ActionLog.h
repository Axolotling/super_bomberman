#pragma once
#include <list>
#include <string>

class ActionLog
{
public:
	enum Tempname
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
	//std::list

	/*
	const std::string separate;
	std::string encapsulate_communicate(std::string temp)
	{
		return std::to_string() + temp + std::to_string(((int)end_rozkaz));
	}*/

	void send_communicates_to_server()
	{
		std::string whole_communicate;
		whole_communicate += concatenate_communicates_from_list();
	}

	std::string concatenate_communicates_from_list()
	{
		std::string result; //+getPlayerId
		result+=";";
		for (std::string one_string: communicates_to_send)
		{
			result += one_string;
		}
		return result;
	}

	std::string getCommunicate(Tempname communicate)
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
			return std::to_string(communicate)+";";
			break;			
		case put_bomb:			
		case erase_crate: 
		case get_bonus: 
		case kill_player: 
		default:;
		}
	}

	std::list<std::string> communicates_to_send;




	void clear_communicates_to_send()
	{
		communicates_to_send.clear();
	}

	void push_communicate(std::string single_communicate)
	{
		communicates_to_send.push_back(single_communicate);
	}

	//lista siê przyda do generowania stringa
	ActionLog();
	~ActionLog();
};

