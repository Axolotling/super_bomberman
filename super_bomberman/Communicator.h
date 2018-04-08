#pragma once
#include <string>

#include <ws2tcpip.h>
#include <winsock2.h>
#include <list>
#include <queue>


#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512            
#define IP_ADDRESS "127.0.0.1"
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

	std::string recieved_message;
	std::queue<std::string> recieved_messages;
	
	


	WSAData wsa_data;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	std::string sent_message = "";
	client_type client = { INVALID_SOCKET, -1, "" };
	int iResult = 0;
	std::string message;

public:
	std::string get_recieved_message()
	{
		return recieved_message;
	}
	void parse_message();
	
	bool is_message_empty()
	{
		return recieved_message.empty();
	}


	void process_client(client_type &new_client);
	bool send_message(std::string message);
	void get_message();


	int connect_to_server();

	void close_connection();

	Communicator();
	~Communicator();
};

