#ifndef SCENE_H
#define SCENE_H

#include "Displayable.h"
#include <list>


class Scene : public Displayable
{
	std::list<Displayable*> displayables;

public:
	void update(sf::Time delta_time) override
	{
		for (Displayable *displayable : displayables)
		{
			displayable->update(delta_time);
		}
	};

	void display(sf::RenderWindow* window) override
	{
		for (Displayable *displayable : displayables)
		{
			displayable->display(window);
		}
	};

	Scene() = default;
	~Scene() = default;

	void add(Displayable *displayable)
	{
		displayables.push_back(displayable);
	};
};

#endif