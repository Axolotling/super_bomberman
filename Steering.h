#pragma once



class Steering
{
public:
	enum Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE
	};
	
	virtual Direction determine_direction() = 0;
	
	Steering() {}
	~Steering() {};


};