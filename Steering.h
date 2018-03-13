#pragma once



class Steering
{
public:
	enum Action
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
		BOMB,
		EXIT
	};
	
	virtual Action determine_direction() = 0;
	
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