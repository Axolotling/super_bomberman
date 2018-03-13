#pragma once


#include <iostream>
#include <ctime>
#include "ViewManager.h"
#include <thread>
#include "Window.h"
#include "BombermanGame.h"
#include "BombermanGameView.h"


using namespace std;


class NeuralNetworkView;

double zwroc1(double x)
{
	return 1/(1+exp(-x));
}

int main()
{
	// NEW COMMENT
	// 2
	srand(time(0));
	const int screen_width = 800;
	const int screen_height = 800;
	const int board_width = 20;
	const int board_height = 20;
	

	
	//Snake* snake = new Snake(board_width,board_height,1, 1, 4);
	//KeyboardSteering *steering = new KeyboardSteering();
	//snake->set_steering(steering);
	//SnakeView *snake_view = new SnakeView(snake);
	//thread thread_snake(&Snake::loop, snake);
	
	ViewManager *manager = new ViewManager;

	BombermanGame bomberman(board_width, board_height);
	BombermanGameView bomberman_view(&bomberman);

	manager->add_view(&bomberman_view, 0, 0, screen_width/board_width,screen_width, screen_height);
	//manager->add_view(nn_view, 0, 0, 5, 600, 750, sf::Color(200, 200, 200));	
	//	manager->add_view(&genetic_algorithm_manager_view,0,0,1,400,750);
	manager->update();
	thread thread_window(&Window::start, Window(screen_width, screen_height, manager));

	//bomberman->loop();
	


	thread_window.join();

	system("pause");
	return 0;
}