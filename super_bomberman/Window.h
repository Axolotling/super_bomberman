#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <list>
#include "ViewManager.h"
#include "MouseInterpreter.h"

using namespace std;


class Window
{
public:
	ViewManager *view_manager;
	MouseInterpreter *mouse_interpreter;
	int width;
	int height;
	
	Window(int width, int height, ViewManager* view_manager) : view_manager(view_manager), width(width), height(height) {};
	
	void start()
	{
		sf::RenderWindow window(sf::VideoMode(width, height), "Bomberman");
		mouse_interpreter = new MouseInterpreter(&window, view_manager);
		window.setFramerateLimit(30);
		bool was_left_button_pressed = false;
		bool was_mousewheel_moved = false;
		sf::Vector2i start_position;
		sf::Vector2i current_position;
		sf::Vector2i saved_position;
		while (window.isOpen())
		{
			mouse_interpreter->handle_mouse();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}		
		
			if (view_manager != nullptr)
			{
				view_manager->update();
		
				for (auto vc : view_manager->views)
				{
					for (auto drawable : vc->view->drawables)
					{
						window.draw(*drawable);
					}
				}
			}
				
				window.display();
				window.clear(sf::Color(10, 10, 10));
		}
	}
	~Window(){};
};

#endif