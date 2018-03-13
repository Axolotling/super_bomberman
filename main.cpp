#pragma once


#include <iostream>
#include <ctime>
#include "ViewManager.h"
#include <thread>
#include "Window.h"
#include "BombermanGame.h"
#include "BombermanGameView.h"


using namespace std;


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

	BombermanGame *bomberman = new BombermanGame(board_width, board_height);
	BombermanGameView bomberman_view(bomberman);


	printf("%d", bomberman);
	
	//Player bartek(bomberman, 1, 1);

	manager->add_view(&bomberman_view, 0, 0, screen_width/board_width,screen_width, screen_height);
	manager->update();

	thread thread_window(&Window::start, Window(screen_width, screen_height, manager));

	//bomberman->loop();
	
	thread_window.join();

	system("pause");
	return 0;
}