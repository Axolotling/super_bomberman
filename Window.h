#pragma once
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
		sf::RenderWindow window(sf::VideoMode(width, height), "Snake");
		mouse_interpreter = new MouseInterpreter(&window, view_manager);
		window.setFramerateLimit(60);
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

		/*	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!is_this_first_click)
				{					
					start_position = sf::Mouse::getPosition();
					is_this_first_click = true;
				}
				else
				{
					current_position = sf::Mouse::getPosition();
				}
				view_manager->view_manager_translation_x = saved_position.x + current_position.x - start_position.x;
				view_manager->view_manager_translation_y = saved_position.y + current_position.y - start_position.y;
				
			
			}
			else
			{
				saved_position.x = view_manager->view_manager_translation_x;
				saved_position.y = view_manager->view_manager_translation_y;
				current_position = start_position = {0,0};
				is_this_first_click = false;
			}
			
			*/
			
		/*
			if (event.type == sf::Event::MouseWheelScrolled && !was_mousewheel_moved)
			{


				was_mousewheel_moved = true;
				if (event.mouseWheelScroll.delta > 0)
				{				
					view_manager->view_manager_scale *= 1.1;
				}
				else if (event.mouseWheelScroll.delta < 0)
				{
					view_manager->view_manager_scale *= 0.9;
				}
			}
			else
			{
				was_mousewheel_moved = false;
			}

			*/
		
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
	
