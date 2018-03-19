#ifndef BOMBERMANGAME_H
#define BOMBERMANGAME_H
#include <list>
#include "BoardObject.h"

class Player;
class Board;

class BombermanGame
{
public:
	Board* board;
	std::list<Player*> players;
	//tymczasowo ¿eby sie kompilowalo
	Player* local_player;

	BombermanGame();

	~BombermanGame() = default;

	double apply_friction_to_speed(const double& friction, double speed);

	// g³ówna pêtla gry
	void loop();
};
#endif