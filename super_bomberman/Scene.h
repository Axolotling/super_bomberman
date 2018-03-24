#ifndef SCENE_H
#define SCENE_H

#include "Displayable.h"


class Scene: public Displayable
{
	std::list<Displayable*> displayables;

public:
	void update() override
	{
		for (Displayable *displayable : displayables)
		{
			displayable->update();
		}
	};

	void display(sf::RenderWindow* window) override
	{
		for (Displayable *displayable: displayables)
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