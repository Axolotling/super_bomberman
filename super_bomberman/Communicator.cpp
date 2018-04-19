#pragma once

#include "Communicator.h"

#include "ActionLog.h"
#include <iostream>
//#include <ws2tcpip.h>
#include <thread>
#include "ServerSteering.h"



void Communicator::proccess_other_players(client_type& new_client)
{
	while (1) {
		memset(new_client.received_message, 0, DEFAULT_BUFLEN);

		if (new_client.socket != 0)
		{
			int iResult = recv(new_client.socket, new_client.received_message, DEFAULT_BUFLEN, 0);

			if (iResult != SOCKET_ERROR) 
			{
				//wyswietl otrzymana wiadomosc
				std::cout << "Otrzymana wiadomosc od serwera to: " << std::endl;
				std::cout << new_client.received_message << std::endl; 

				/*for (int i = 2; i < std::strlen(new_client.received_message); i++)
				{
					if (new_client.received_message[i] == '_')
					{
						std::cout << "Wiele komunikatow polaczone w jeden :o" << endl;
					}
				}*/

				//wrzuc do kolejki do przetwarzania otrzymywanych wiadomosci
				recieved_messages.push(new_client.received_message);

				//przetwarzanie kazdej kolejnej wiadomosci? uzywac mutexow? wywolanie dopiero gdzie� p�niej przetwarzania?
				//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
				//ServerSteering::parse_message(recieved_message);
				//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

				//std::cout << "Pushowanko do kolejeczki takiego czegos: " << recieved_message<< std::endl;
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

	//getline(std::cin, sent_message); // zamiast get line bedziemy wysylac actionloga  <<------------- WA�NE
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


//odbieranie kolejnych wiadomosci od serwera
/*
void Communicator::get_message()
{	
	recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);
	message = client.received_message;	
}
*/

bool Communicator::connect_to_server()
{
	std::cout << "Tworzenie nowego klienta...\n";

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != 0)
	{
		std::cout << "WSAStartup() failed with error: " << iResult << std::endl;
		return false;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::cout << "Laczenie...\n";

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

	std::cout << "Pomyslnie polaczono z serwerem!" << std::endl;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//Obtain id from server for this client;	
	
	
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	return true;
}

void Communicator::get_player_id_from_server()
{
	//odebranie id gracza od serwera
	std::cout << "Pobieram z serwera moje id" << std::endl;
	recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);
	message = client.received_message;
	client.id = atoi(client.received_message);

	
	
	if (message != "Server is full"){

		std::cout << "Pobieram z serwera seed do mapy" << std::endl;
		recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);
		message = client.received_message;
		set_seed(atoi(client.received_message));
		std::cout << "Otrzymany seed to : " << get_seed() << std::endl;
		//tworzenie watku do odbierania wiadomosci od pozostalych graczy
		std::thread my_thread(&Communicator::proccess_other_players, this, client);
		
		//dzialanie niezalezne w watku
		my_thread.detach();
	}
	else
		std::cout << client.received_message << std::endl;

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
	//jezeli pomyslnie polaczono z serwerem odbierz id w celu ustawienia pozycji na mapie
	if (connect_to_server()) get_player_id_from_server();	
}




Communicator::~Communicator()
{
	close_connection();
}

//obecna liczba graczy w grze
int Communicator::get_current_player_number()
{
	return this->current_player_numbers;
}

void Communicator::set_current_player_number(const int n)
{
	this->current_player_numbers = n;
}
