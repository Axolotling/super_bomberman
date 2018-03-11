#pragma once

#include "View.h"

#include <list>

using namespace std;


class ViewManager
{
	// Public definitions
public:
	struct ViewContainer
	{
		View* view;

		double x;
		double y;		
		double width;
		double height;

		double inner_offset_x;
		double inner_offset_y;
		double scale;

		sf::Color background_color;

		ViewContainer(View *view, double x = 0.0, double y = 0.0, double scale = 1.0, double background_width = 0.0, double background_height = 0.0, sf::Color background_color = sf::Color::Black)
		{
			this->view = view;
			this->x = x;
			this->y = y;			
			this->scale = scale;
			this->width = background_width;
			this->height = background_height;
			this->background_color = background_color;
			this->inner_offset_x = 0;
			this->inner_offset_y = 0;
		}
	};


	// Private fields

	// Public fields
public:
	list<ViewContainer*> views;

	// Constructors and destructors
	ViewManager() {};
	~ViewManager() {};
	// Private methods

	// Public methods
public:
	void update()
	{
		for (auto i : views)
		{
			i->view->update(i->x, i->y, i->width, i->height, i->inner_offset_x, i->inner_offset_y, i->scale, i->background_color);
		}
	}

	void add_view(View* view, double x = 0, double y = 0, double scale = 1, double background_width = 0.0, double background_height = 0.0, sf::Color background_color = sf::Color::Black)
	{
		views.push_front(new ViewContainer(view, x, y, scale, background_width, background_height, background_color));
	}

/*	double view_manager_translation_x = 0;
	double view_manager_translation_y = 0;
	double view_manager_scale = 1;
	*/	


	

};