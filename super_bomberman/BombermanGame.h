#ifndef BOMBERMANGAME_H
#define BOMBERMANGAME_H
#include <list>
#include "BoardObject.h"


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
	// plansza - zawiera informacje o tym co znajduje si� w ka�dym miejscu planszy
//<<<<<<< HEAD
	//BoardObject ***board; //board[x][y]->metoda() pozwala wywo�a� metod� obiektu
	// wymiary siatki planszy gry
	int board_width, board_height;
//=======
	Board* board;
//>>>>>>> dcf9718d0f66ec0b7934243d2076119288088ee1
	std::list<Player*> players;
	Player* local_player;

	int publiczne_cos = 2;

// Constructors and destructors
//<<<<<<< HEAD
//	BombermanGame(const int& board_width, const int& board_height);;
	
//=======
	BombermanGame();

//>>>>>>> dcf9718d0f66ec0b7934243d2076119288088ee1
	~BombermanGame() = default;

// Private methods
	double apply_friction_to_speed(const double& friction, double speed);
// Public methods

	// g��wna p�tla gry
	void loop();
};




// Public definitions
// Private fields
// Public fields
// Constructors and destructors
// Private methods
// Public methods

#endif