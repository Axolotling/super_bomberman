#pragma once
#include <string>

#include <ws2tcpip.h>
#include <winsock2.h>
#include <list>
#include <queue>
#include<thread>


#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512            
#define IP_ADDRESS "192.168.43.46"
#define DEFAULT_PORT "3504"

class Communicator
{
	struct client_type
	{
		SOCKET socket;
		int id;		
		char received_message[DEFAULT_BUFLEN];
		//client_type(){}
	};

	int seed;

	std::string recieved_message;
	std::queue<std::string> recieved_messages;

	//dane adresowe do komunikacji sieciowej
	WSAData wsa_data;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	std::string sent_message = "";
	client_type client = { INVALID_SOCKET, -1, "" };
	int iResult = 0;
	int current_player_numbers = 0;
	std::string message;

public:
	client_type* get_client()
	{
		return &this->client;
	}

	int get_seed()
	{
		return  this->seed;
	}

	void set_seed(int seed)
	{
		this->seed = seed;
	}

	std::string pop_first_recieved_message()
	{
		std::string result = recieved_messages.front();
		recieved_messages.pop();
		return result;
	}

	void push_message(std::string message)
	{
		recieved_messages.push(message);
	}

	/*std::queue<std::string>* pop_first_recieved_messages_list()
	{
		return &recieved_messages;
	}*/

	//parsowanie przerzucone do ServerSteering
	//void parse_message();
	
	bool is_message_list_empty()
	{
		if (recieved_messages.empty() == false)
		{
			//just for debug
			int x = 2;
		};

		return recieved_messages.empty();
	}


	
	//czasowo nie uzywac (brak uzasadnienia do uzycia - zastapione przez procces_other_players)
	//void get_message();


	bool connect_to_server();
	void get_player_id_from_server();
	void proccess_other_players(client_type &new_client);
	bool send_message(std::string message);
	void close_connection();

	Communicator();
	~Communicator();
	int get_current_player_number();
	void set_current_player_number(int n);
};

