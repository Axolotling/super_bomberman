#ifndef MOUSEINTERPRETER_H
#define MOUSEINTERPRETER_H

#include <SFML/Window/Mouse.hpp>

class MouseInterpreter 
{
public:
	ViewManager *view_manager;
	sf::Window *sfwindow;

	ViewManager::ViewContainer* getTargetView()
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(*sfwindow);
		int mouse_x = mouse_position.x;
		int mouse_y = mouse_position.y;
		
		ViewManager::ViewContainer* result = nullptr;
		
		for (ViewManager::ViewContainer* i: view_manager->views)
		{
			if (mouse_x >= i->x && mouse_x <= i->x + i->width)
			{
				if (mouse_y >= i->y && mouse_y <= i->y + i->height)
				{
					result = i;
				}
			}
		}
		return result;
	}
	bool is_this_first_click = true;
	bool was_mousewheel_moved = false;
	sf::Vector2i start_position;
	sf::Vector2i current_position;
	sf::Vector2i start_relative_position = { 0,0 };
	sf::Vector2i relative_position = {0,0};
	ViewManager::ViewContainer *target_view = nullptr;

	MouseInterpreter(sf::Window *sfwindow, ViewManager *view_manager) : view_manager(view_manager), sfwindow(sfwindow) {
		
	}

	void handle_mouse()
	{
		bool lmb_pressed = false;
		bool rmb_pressed = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			lmb_pressed = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			rmb_pressed = true;

		if (rmb_pressed == lmb_pressed)
		{
			lmb_pressed = rmb_pressed = false;
		}


		if (lmb_pressed || rmb_pressed)
		{
			if (is_this_first_click)
			{
				start_position = sf::Mouse::getPosition(*sfwindow);
				current_position = start_position;
				is_this_first_click = false;
				target_view = getTargetView();
				if (target_view != nullptr)
				{
					relative_position = { (int)(start_position.x - target_view->x),(int)(start_position.y - target_view->y) };
					start_relative_position = { (int)target_view->inner_offset_x, (int)target_view->inner_offset_y };
				}
			}
			else
			{
				current_position = sf::Mouse::getPosition(*sfwindow);
				
			}
			//ViewManager::ViewContainer *target_view = getTargetView();
			if (target_view != nullptr)
			{
				if (rmb_pressed)
				{
					int x_difference = current_position.x - start_position.x;
					int y_difference = current_position.y - start_position.y;
					target_view->inner_offset_x = x_difference + start_relative_position.x;// -relative_position.x;
					target_view->inner_offset_y = y_difference + start_relative_position.y;// -relative_position.y;
					//relative_position.x = target_view->inner_offset_x;
					//relative_position.y = target_view->inner_offset_y;
				}
				else //lmb_pressed
				{
					target_view->x = current_position.x - relative_position.x;//saved_position.x + current_position.x - start_position.x;
					target_view->y = current_position.y - relative_position.y;// 10;//saved_position.y + current_position.y - start_position.y;
				}
			}		


		}
		else
		{
			//ViewManager::ViewContainer *target_view = getTargetView();
			/*if (target_view != nullptr)
			{
				saved_position.x = target_view->x;
				saved_position.y = target_view->y;
			}*/
		
			//current_position = start_position = { 0,0 };
			is_this_first_click = true;
		}
		/*
		sf::Event event;
		
		if (event.type == sf::Event::MouseWheelScrolled && !was_mousewheel_moved)
		{


			was_mousewheel_moved = true;
			if (event.mouseWheelScroll.delta > 0)
			{
				//view_manager->view_manager_scale *= 1.1;
			}
			else if (event.mouseWheelScroll.delta < 0)
			{
				//view_manager->view_manager_scale *= 0.9;
			}
		}
		else
		{
			was_mousewheel_moved = false;
		}
		*/
	}

};
#endif