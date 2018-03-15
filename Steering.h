#ifndef STEERING_H
#define STEERING_H


class Steering
{
public:
	enum Action
	{
		GO_UP,
		GO_RIGHT,
		GO_DOWN,
		GO_LEFT,
		NONE,
		BOMB,
		EXIT
	};
	
	virtual Action determine_action() = 0;
	
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