#include "Player.h"
#include "Board.h"
#include "Bomb.h"
#include "WsadKeyboardSteering.h"
#include "ServerSteering.h"

#define epsilon 0.1

Player::Player(Board* board, const double& board_x, const double& board_y, int id, ActionLog *action_log,Communicator *communicator): BoardObject(board, board_x, board_y, true, true)
{
	this->communicator = communicator;
	setId(id);
	exact_x = board_x;
	exact_y = board_y;
	this->action_log = action_log;
	//std::cout << "Created Player Object" << std::endl;
	if (!texture->loadFromFile("player.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTexture(*texture);
	steering = new ServerSteering(getId(), board);
	
}

Player::~Player()
{
}

void Player::make_speed_smaller_or_equal_max()
{
	if (speed_x * speed_y != 0)
	{
		double speed = sqrt(speed_x * speed_x + speed_y * speed_y);

		if (speed > max_speed)
		{
			double S = max_speed / speed;
			speed_x = speed_x * S;
			speed_y = speed_y * S;
		}
	}
	else
	{
		if (speed_x > max_speed)
		{
			speed_x = max_speed;
		}
		else if (speed_y > max_speed)
		{
			speed_y = max_speed;
		}
		else if (speed_y < -max_speed)
		{
			speed_y = -max_speed;
		}
		else if (speed_x < -max_speed)
		{
			speed_x = -max_speed;
		}
	}
}

void Player::apply_friction_to_speed(const sf::Time& delta_time)
{
	if (speed_x > 0)
	{
		speed_x -= friction * delta_time.asSeconds();
		if (speed_x < 0) speed_x = 0;
	}
	else
	{
		speed_x += friction * delta_time.asSeconds();
		if (speed_x > 0) speed_x = 0;
	}


	if (speed_y > 0)
	{
		speed_y -= friction * delta_time.asSeconds();
		if (speed_y < 0) speed_y = 0;
	}
	else
	{
		speed_y += friction * delta_time.asSeconds();
		if (speed_y > 0) speed_y = 0;
	}
}

bool Player::is_object_on_field(int checked_x, int checked_y)
{
	BoardObject* checked_field = board->get_object({ checked_x, checked_y });
	if (checked_field != nullptr && checked_field->can_be_collided)
	{
		return true;
	}
	return false;
}


bool Player::is_there_collision_on_the_right()
{
	if (is_object_on_field(exact_x + 1.0, exact_y + epsilon)) return true;
	if (is_object_on_field(exact_x + 1.0, exact_y + 1.0 - epsilon)) return true;
	return false;
}


bool Player::is_there_collision_on_the_left()
{
	if (is_object_on_field(exact_x, exact_y + epsilon)) return true;
	if (is_object_on_field(exact_x, exact_y + 1.0 - epsilon)) return true;
	return false;
}

bool Player::is_there_collision_on_the_top()
{
	if (is_object_on_field(exact_x + epsilon, exact_y)) return true;
	if (is_object_on_field(exact_x + 1.0 - epsilon, exact_y)) return true;
	return false;
}

bool Player::is_there_collision_on_the_bottom()
{
	if (is_object_on_field(exact_x + epsilon, exact_y + 1.0)) return true;
	if (is_object_on_field(exact_x + 1.0 - epsilon, exact_y + 1.0)) return true;
	return false;
}

void Player::update(sf::Time delta_time)
{
	if(ServerSteering *server_steering = dynamic_cast<ServerSteering*>(steering))
	{
		string message;
		while (!communicator->is_message_list_empty())
		{
			message = communicator->pop_first_recieved_message();
			if (!message.empty())
			{
				server_steering->parse_message(message);
			}
			else
			{
				cout << "Otrzymalismy pusta wiadomosc :/" << endl;
			}
		}

		/*
		if (!communicator->is_message_empty())
		{
			server_steering->parse_message(communicator->get_recieved_message());
		}*/
	}
	for (Steering::Action action : steering->determine_action())
	{
		switch (action)
		{
		case Steering::GO_RIGHT:
			//exact_x += speed_x * delta_time.asSeconds();
			speed_x += acceleration * delta_time.asSeconds();
			break;
		case Steering::GO_LEFT:
			//exact_x -= speed_x * delta_time.asSeconds();
			speed_x -= acceleration * delta_time.asSeconds();
			break;
		case Steering::GO_UP:
			speed_y -= acceleration * delta_time.asSeconds(); //exact_y -= speed_y * delta_time.asSeconds();
			break;
		case Steering::GO_DOWN:
			speed_y += acceleration * delta_time.asSeconds();
			//exact_y += speed_y * delta_time.asSeconds();
			break;
		case Steering::BOMB:
			int bomb_x = exact_x + 0.5;
			int bomb_y = exact_y + 0.5;
			BoardObject *board_object = board->get_object({ bomb_x, bomb_y });
			if (board_object == nullptr)
			{
				assert(board_object == nullptr);
				board->set_object({ bomb_x, bomb_y }, new Bomb(board, bomb_x, bomb_y));
				assert(board->get_object({ bomb_x, bomb_y }) != nullptr);
			}			
			break;
		}
	}
	apply_friction_to_speed(delta_time);
	make_speed_smaller_or_equal_max();

	exact_x = exact_x + speed_x * delta_time.asSeconds();
	exact_y = exact_y + speed_y * delta_time.asSeconds();
	action_log->set_current_pos_x(exact_x);
	action_log->set_current_pos_y(exact_y);

	if (speed_x > 0)
	{
		if (is_there_collision_on_the_right())
		{
			exact_x = static_cast<int>(exact_x);
			speed_x = 0;
		}
	}
	else
	{
		if (is_there_collision_on_the_left()) 
		{
			exact_x = static_cast<int>(exact_x + 1.0);
			speed_x = 0;
		}
	}

	if (speed_y > 0)
	{
		if (is_there_collision_on_the_bottom())
		{
			exact_y = static_cast<int>(exact_y);
			speed_y = 0;
		}
	}
	else
	{
		if (is_there_collision_on_the_top()) {
			exact_y = static_cast<int>(exact_y + 1.0);
			speed_y = 0;
		}
	}
	
	BoardObject::update(delta_time);
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setPosition(grid_cell_side * exact_x, grid_cell_side * exact_y);
}
