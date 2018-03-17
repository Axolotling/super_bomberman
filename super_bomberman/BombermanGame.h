#ifndef BOMBERMANGAME_H
#define BOMBERMANGAME_H
#include <list>


class Player;
class Board;

class BombermanGame
{
// Public definitions
public:
	///none

// Private fields
private:
	Player* add_player(int x, int y);

// Public fields
public:
	// plansza - zawiera informacje o tym co znajduje siê w ka¿dym miejscu planszy
	Board* board;
	std::list<Player*> players;
	Player* local_player;

	int publiczne_cos = 2;

// Constructors and destructors
	BombermanGame();

	~BombermanGame() = default;

// Private methods
	double apply_friction_to_speed(const double& friction, double speed);
// Public methods

	// g³ówna pêtla gry
	void loop();
};




// Public definitions
// Private fields
// Public fields
// Constructors and destructors
// Private methods
// Public methods

#endif