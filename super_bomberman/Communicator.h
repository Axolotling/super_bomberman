#pragma once
#include <string>

class Communicator
{
	std::string recieved_message;
public:
	void parse_message();
	void send_message(std::string message);

	Communicator();
	~Communicator();
};

