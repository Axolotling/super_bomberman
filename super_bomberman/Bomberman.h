#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include <memory>
#include <iostream>
#include "Board.h"
#include "Crate.h"
#include "Rock.h"
#include "Player.h"

class Bomberman
{
public:
	Bomberman()
	{
		std::cout << "Created Bomberman Object" << endl;
		int window_height = 960; 
		int window_width = 1280;

		const int framerate = 30;
		

		std::unique_ptr<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(window_width, window_height), "Bomberman"));
		window->setFramerateLimit(framerate);
		
		sf::Event event;
		sf::Clock clock;
		sf::Time last_update_time = clock.getElapsedTime();

		Scene *scene = new Scene;
		Board* board = new Board(1);
		//scene->add(new Crate(board, 2, 2));
		//scene->add(new Rock(board, 3, 2));
		//scene->add(new Player(board, 3, 3));
		scene->add(board);
		while (window->isOpen())
		{			
			const sf::Time delta_time = clock.getElapsedTime() - last_update_time;
			last_update_time = clock.getElapsedTime();

			while (window->pollEvent(event))	if (event.type == sf::Event::Closed) window->close();

			//std::cout << delta_time.asSeconds() << std::endl;


			scene->update(delta_time);
			scene->display(window.get());
			window->display();
			window->clear();
		}

	}
	~Bomberman() = default;
};
