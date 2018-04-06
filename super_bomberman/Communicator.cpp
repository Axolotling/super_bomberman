#include "Communicator.h"
#include <wincon.h>
#include "ActionLog.h"

void Communicator::parse_message()
{
	recieved_message;
	std::string temp = recieved_message.substr(0, 1);
	int id = atoi(temp.data()); 

	while(1)
	{
		int i = 1;

		if (recieved_message[i] == ActionLog::start_rozkaz)
		{
			while (recieved_message[i] != ActionLog::end_rozkaz)
			{
				
			}
		}


	}
}

void Communicator::send_message(std::string message)
{
}

Communicator::Communicator()
{

}




Communicator::~Communicator()
{
}
