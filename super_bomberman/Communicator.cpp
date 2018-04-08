#pragma once

#include "Communicator.h"

#include "ActionLog.h"
#include <iostream>
//#include <ws2tcpip.h>
#include <thread>



void Communicator::parse_message()
{
	recieved_message;
	std::string temp = recieved_message.substr(0, 1);
	int id = atoi(temp.data()); 

/*	while(1)
	{
		int i = 1;


		//if (recieved_message[i] == ';')
		
	}*/

}






void Communicator::process_client(client_type& new_client)
{
	while (2137) {
		memset(new_client.received_message, 0, DEFAULT_BUFLEN);

		if (new_client.socket != 0)
		{
			int iResult = recv(new_client.socket, new_client.received_message, DEFAULT_BUFLEN, 0);

			if (iResult != SOCKET_ERROR) 
			{
				std::cout << new_client.received_message << std::endl;//tu bêdzie wywo³ywana metoda od parsowania zachowañ graczy
				recieved_messages.push(recieved_message);
			}

			else
			{
				std::cout << "recv() failed: " << WSAGetLastError() << std::endl;
			}
		}
		if (WSAGetLastError() == WSAECONNRESET)
			std::cout << "The server has disconnected" << std::endl;
	
	}
		
}

bool Communicator::send_message(std::string message)
{

	//getline(std::cin, sent_message); // zamiast get line bedziemy wysylac actionloga  <<------------- WA¯NE
	iResult = send(client.socket, message.c_str(), strlen(message.c_str()), 0);

	if (iResult <= 0)
	{
		std::cout << "send() failed: " << WSAGetLastError() << std::endl;
		return false;
		//	break;
	}
	return true;
	//Sleep(1000);

}

void Communicator::get_message()
{
	recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);
	message = client.received_message;

	if (message != "Server is full")
	{
		client.id = atoi(client.received_message);

		std::thread my_thread(&Communicator::process_client, this, client);

		//process_client(client);

		//send_message();

		//Shutdown the connection since no more data will be sent
		my_thread.detach();
	}
	else
		std::cout << client.received_message << std::endl;
}

int Communicator::connect_to_server()
{
	std::cout << "Starting Client...\n";

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != 0)
	{
		std::cout << "WSAStartup() failed with error: " << iResult << std::endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::cout << "Connecting...\n";

	// Resolve the server address and port
	iResult = getaddrinfo(IP_ADDRESS, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		std::cout << "getaddrinfo() failed with error: " << iResult << std::endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		client.socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (client.socket == INVALID_SOCKET)
		{
			std::cout << "socket() failed with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			system("pause");
			return 1;
		}

		// Connect to server.
		iResult = connect(client.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(client.socket);
			client.socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (client.socket == INVALID_SOCKET)
	{
		std::cout << "Unable to connect to server!" << std::endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	std::cout << "Successfully Connected" << std::endl;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//Obtain id from server for this client;
	
	
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	return 0;
}

void Communicator::close_connection()
{
	std::cout << "Shutting down socket..." << std::endl;
	iResult = shutdown(client.socket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "shutdown() failed with error: " << WSAGetLastError() << std::endl;
		closesocket(client.socket);
		WSACleanup();
	}

	closesocket(client.socket);
	WSACleanup();
}

Communicator::Communicator()
{	
	connect_to_server();
	//std::thread communication_thread(&Communicator::send_message, this);
	//communication_thread.detach();
}




Communicator::~Communicator()
{
	close_connection();
}
