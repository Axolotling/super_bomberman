#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include <memory>
#include <iostream>
#include "Board.h"
#include "Crate.h"
#include "Communicator.h"


class Bomberman
{
public:
	Bomberman()
	{		
		Communicator *communicator = new Communicator;
		communicator->get_message();



		int window_height = 720; 
		int window_width = 1080;
		const int framerate = 30;	

		std::unique_ptr<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(window_width, window_height), "Bomberman"));
		window->setFramerateLimit(framerate);
		ActionLog action_log(1);


		sf::Event event;
		sf::Clock clock;
		sf::Time last_update_time = clock.getElapsedTime();

		Scene *scene = new Scene;
		Board* board = new Board(2, &action_log, communicator);

		scene->add(board);


		
		float remembered_time = clock.getElapsedTime().asSeconds();
		while (window->isOpen())
		{			
			const sf::Time delta_time = clock.getElapsedTime() - last_update_time;
			last_update_time = clock.getElapsedTime();

			while (window->pollEvent(event))	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window->close();

			if (!action_log.is_empty())
			{
				if(!communicator->send_message(action_log.create_final_message_from_list()))
				{
					cout << "Wyslanie nie powiodlo sie :(" << endl;
				};
				action_log.clear_communicates_to_send();
			}

		

			/*if (clock.getElapsedTime().asSeconds() >= remembered_time+1)
			{
				communicator->get_message(); //otrzymywanie wiadomosci od serwera
				cout << "poke" << endl;
				remembered_time = clock.getElapsedTime().asSeconds();
			}*/
			

		
			scene->update(delta_time);
			scene->display(window.get());
			window->display();
			window->clear();
		}
	}

	~Bomberman() = default;
};
