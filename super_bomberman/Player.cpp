#include "Player.h"
#include "Board.h"

Player::Player(Board* board, const double& board_x, const double& board_y): BoardObject(
	board, board_x, board_y, true, true)
{
	exact_x = board_x;
	exact_y = board_y;
	this->board = board;
	//std::cout << "Created Player Object" << std::endl;
	if (!texture->loadFromFile("player.png"))
	{
		std::cout << "Grafika obiektu siê nie za³adowa³a";
	}
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setTexture(*texture);
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
			std::cout << "SX=" << speed_x << " SY=" << speed_y << std::endl;
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

//tu powstaje error przy get object
bool Player::is_there_collision_on_the_right()
{
	int checked_x = exact_x + 1.0;
	int checked_y = exact_y;
	BoardObject* checked_field = board->get_object({checked_x, checked_y});
	if (checked_field != nullptr && checked_field->can_be_collided)
	{
		return true;
	}

	checked_y = exact_y + 1;
	checked_field = board->get_object({checked_x, checked_y});
	if (checked_field != nullptr && checked_field->can_be_collided)
	{
		return true;
	}

	//fa³sz gdy nie znaleziono kolizji z prawej
	return false;
}

void Player::update(sf::Time delta_time)
{
	for (Steering::Action action : steering.determine_action())
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
		}
	}
	apply_friction_to_speed(delta_time);
	make_speed_smaller_or_equal_max();

	double new_x = exact_x + speed_x * delta_time.asSeconds();
	double new_y = exact_y + speed_y * delta_time.asSeconds();

	exact_x = new_x;
	exact_y = new_y;
	if (is_there_collision_on_the_right()) exact_x = static_cast<int>(exact_x);

	BoardObject::update(delta_time);
	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable);
	sprite->setPosition(grid_cell_side * exact_x, grid_cell_side * exact_y);
}
