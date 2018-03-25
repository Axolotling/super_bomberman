#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <list>
#include "ViewManager.h"
#include "MouseInterpreter.h"
#include "KeyboardSteering.h"
#include "Scene.h"
#include "Crate.h"
#include "BombermanGame.h"
#include "Board.h"

using namespace std;


class Window
{
public:
	ViewManager *view_manager;
	
	
	int width;
	int height;
	sf::Clock clock;

	double apply_friction_to_speed(const double & friction, double speed)
	{
		if (speed < friction && speed > -friction)
		{
			speed = 0;
		}
		else
		{
			if (speed > 0) speed -= friction;
			if (speed < 0) speed += friction;
		}
		return speed;
	}



	Window(int width, int height, ViewManager* view_manager) : view_manager(view_manager), width(width), height(height) {};
	
	void start()
	{
		Player* local_player = new Player(new BombermanGame,1,1);
		

		const int framerate = 30;
		const double milliseconds_per_frame = 1000 / framerate;
		int time_of_last_frame = 0;

		double a_per_second = 0.4;
		double a_per_frame = a_per_second / framerate;
		
		double friction_per_second = 0.4;
		double friction_per_frame = friction_per_second / framerate;

		double max_v_fields_per_second = 6;
		double max_v_fields_per_frame = max_v_fields_per_second / framerate;


		sf::RenderWindow window(sf::VideoMode(width, height), "Bomberman");
		window.setFramerateLimit(framerate);

		Steering* steering = new KeyboardSteering;
		MouseInterpreter *mouse_interpreter = new MouseInterpreter(&window, view_manager);;

		sf::Font font;
		font.loadFromFile("bahnschrift.ttf");


		Scene *scene = new Scene;
		auto a = new sf::RectangleShape(sf::Vector2f(200, 200));
		a->setPosition(100, 100);
		
		Scene *scene2 = new Scene;

		Crate *crate = new Crate(new BombermanGame(),2,2);

		auto board = new Board(new BombermanGame(), 1);
		//this->local_player = this->players.front();
		
		scene2->add(crate);
		scene->add(board);
		scene->add(local_player);
		while (window.isOpen())
		{
			mouse_interpreter->handle_mouse();

			sf::Event event;
			while(window.pollEvent(event))	if(event.type == sf::Event::Closed) window.close();
			

			/*
			if (view_manager != nullptr)
			{
				//Z£O
				view_manager->update();
		
				for (auto vc : view_manager->views)
				{
					for (auto drawable : vc->view->drawables)
					{
						window.draw(*drawable);
					}
				}
			}
			*/
							
			//Player* local_player;

			while (clock.getElapsedTime().asMilliseconds() >= time_of_last_frame + milliseconds_per_frame)
			{					
				time_of_last_frame = time_of_last_frame + int(milliseconds_per_frame);				


				
				if (local_player->board_x < board->get_map_size().first - 1)
				{
					bool pressed_up_or_down = false;
					bool pressed_left_or_right = false;

					for (auto action : steering->determine_action()) 
					{
						switch (action)
						{
						case Steering::GO_UP:
							pressed_up_or_down = true;
							local_player->y_velocity += -a_per_frame;
							if (local_player->y_velocity < -max_v_fields_per_frame) local_player->y_velocity = -max_v_fields_per_frame;
							break;
						case Steering::GO_DOWN:
							pressed_up_or_down = true;
							local_player->y_velocity += a_per_frame;
							if (local_player->y_velocity > max_v_fields_per_frame) local_player->y_velocity = max_v_fields_per_frame;
							break;
						case Steering::GO_LEFT:
							pressed_left_or_right = true;
							local_player->x_velocity += -a_per_frame;
							if (local_player->x_velocity < -max_v_fields_per_frame) local_player->x_velocity = -max_v_fields_per_frame;
							break;
						case Steering::GO_RIGHT:
							std::cout << "right, position " << local_player->exact_x << ", " << local_player->exact_y << endl;
							pressed_left_or_right = true;
							local_player->x_velocity += a_per_frame;
							if (local_player->x_velocity > max_v_fields_per_frame) local_player->x_velocity = max_v_fields_per_frame;
							break;
						case Steering::NONE:
							break;
						default:
							break;
						}

						}
						if (!pressed_left_or_right)
							local_player->x_velocity = apply_friction_to_speed(friction_per_frame, local_player->x_velocity);

						if (!pressed_up_or_down)
							local_player->y_velocity = apply_friction_to_speed(friction_per_frame, local_player->y_velocity);
					}
					local_player->move_player(local_player->x_velocity, local_player->y_velocity);
				}

			




			
			
			scene->update();
			scene->display(&window);
			//test
			sf::Time current_time = clock.getElapsedTime();			
			sf::Text text(std::to_string(current_time.asMilliseconds()), font);			
			text.setFillColor(sf::Color::Red);
			window.draw(text);
			//test_end
			

			window.display();
			window.clear(sf::Color(10, 10, 10));
		}
		delete scene;
	}
	~Window(){};
};

#endif