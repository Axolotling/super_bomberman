#ifndef STEERING_H
#define STEERING_H
#include <list>


class Steering
{
	bool was_up_key_pressed = false;
	bool was_down_key_pressed = false;
	bool was_left_key_pressed = false;
	bool was_right_key_pressed = false;
public:

	bool get_was_up_key_pressed() const
	{
		return was_up_key_pressed;
	}

	void set_was_up_key_pressed(bool was_up_key_pressed)
	{
		this->was_up_key_pressed = was_up_key_pressed;
	}

	bool get_was_down_key_pressed() const
	{
		return was_down_key_pressed;
	}

	void set_was_down_key_pressed(bool was_down_key_pressed)
	{
		this->was_down_key_pressed = was_down_key_pressed;
	}

	bool get_was_left_key_pressed() const
	{
		return was_left_key_pressed;
	}

	void set_was_left_key_pressed(bool was_left_key_pressed)
	{
		this->was_left_key_pressed = was_left_key_pressed;
	}

	bool get_was_right_key_pressed() const
	{
		return was_right_key_pressed;
	}

	void set_was_right_key_pressed(bool was_right_key_pressed)
	{
		this->was_right_key_pressed = was_right_key_pressed;
	}


	enum Action
	{
		GO_UP,
		GO_RIGHT,
		GO_DOWN,
		GO_LEFT,
		BOMB,
		EXIT,
		NONE
	};
	
	virtual std::list<Action> determine_action() = 0;
	
	Steering() {}
	~Steering() {};


};


/*
#pragma once
#include <queue>


class Steering
{
public:
	enum Direction
	{
		up,
		right,
		down,
		left,
		bomb,
		exit
	};
	
	//virtual priority_queue<Action> determine_action() = 0;
	virtual Direction determine_action() = 0;
	

	Steering()
	{
	}
	~Steering() {};

};

 *
 */

#endif