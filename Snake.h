#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <thread>
#include "KeyboardSteering.h"
#include <SFML/System.hpp>

using namespace std;


class Snake
{
	// Definicje publiczne
public:
	class Segment
	{
	public:
		int x;
		int y;
		Segment(int x, int y) : x(x), y(y) {};
		~Segment() = default;
	};


	// Pola prywatne
private:
	bool ate = false;
	bool lost = false;
	bool tick = true;
	int last_tick;
	sf::Clock clock;
	const int milliseconds_between_ticks = 200;
	Steering *steering = nullptr;
	Steering::Action direction;


	// Pola publiczne
public:
	const int board_width;
	const int board_height;
	int food_x;
	int food_y;
	list<Segment*> body;
	

	// Konstruktory i destruktory
	Snake(int board_width, int board_height, int x, int y, int length) : board_width(board_width), board_height(board_height)
	{
		body.push_back(new Segment(x, y));
		for (int i = 1; i < length; i++)
		{
			body.push_back(new Segment(x, ++y));
		}
		direction = Steering::GO_UP;

		determine_new_food_position();
	}

	~Snake() = default;


	// Metody prywatne
private:
	void determine_new_food_position()
	{
		bool is_position_proper = true;
		food_x = rand() % board_width;
		food_y = rand() % board_height;
		do {

			for (auto segment : body)
			{
				if (segment->x == food_x && segment->y == food_y)
				{
					is_position_proper = false;
					break;
				}
			}
		} while (!is_position_proper);
	}


	// Metody publiczne
public:

	void loop(int ticks = -1)
	{
		while (steering == nullptr);




		last_tick = clock.getElapsedTime().asMilliseconds();	
		
		while (!lost)
		{
			Steering::Action temp_direction = steering->determine_action();
			if (temp_direction != Steering::NONE && temp_direction != direction - 2 && temp_direction != direction + 2)
			{
				direction = temp_direction;
			}

			if (!tick && clock.getElapsedTime().asMilliseconds() >= last_tick + milliseconds_between_ticks)
			{
				last_tick += milliseconds_between_ticks;
				tick = true;
			}
			if (tick)
			{
				if (ticks-- == 0)
				{
					break;
				}
				tick = false;

				

				double previous_x = body.front()->x, previous_y = body.front()->y;
				
				for (auto segment : body)
				{

					if (segment == body.front())
					{
						previous_x = segment->x;
						previous_y = segment->y;
						switch (direction)
						{
						case Steering::GO_UP:		segment->y--;
							break;
						case Steering::GO_DOWN:	segment->y++;
							break;
						case Steering::GO_LEFT:	segment->x--;
							break;
						case Steering::GO_RIGHT:	segment->x++;
							break;
						}
						if (segment->x >= board_width)
							segment->x = 0;
						else if (segment->x < 0)
							segment->x = board_width - 1;
						if (segment->y >= board_height)
							segment->y = 0;
						if (segment->y < 0)
							segment->y = board_height - 1;
					}
					else
					{
						double tmp_x = segment->x;
						double tmp_y = segment->y;
						segment->x = previous_x;
						segment->y = previous_y;
						previous_x = tmp_x;
						previous_y = tmp_y;
					}

				}
				if (ate)
				{
					body.push_back(new Segment(previous_x, previous_y));					
					ate = false;
				}				
				for (auto segment : body)
				{
					if (segment != body.front() && segment->x == body.front()->x && segment->y == body.front()->y)
					{
						lost = true;
					}
				}
				if (body.front()->x == food_x && body.front()->y == food_y)
				{
					ate = true;
					determine_new_food_position();
				}
			}
		}
	}	

	void set_steering(Steering *steering)
	{
		this->steering = steering;
	}	

};

#endif