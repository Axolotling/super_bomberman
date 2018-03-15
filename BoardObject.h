#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H


class BombermanGame;

// Klasa abstrakcyjna, która opisuje obiekt który może zostać umieszczony na planszy gry
class BoardObject
{
// Public definitions
	///none
// Private fields

// Protected fields
protected:
	
// Public fields
public:
	// Gdzie na planszy znajduje się obiekt
	int board_x, board_y;
	bool can_be_broken;
	bool can_be_collided;
	BombermanGame* bomberman_game;

// Constructors and destructors
	BoardObject(BombermanGame* bomberman_game, const int &board_x, const int &board_y, bool can_be_broken = true, bool can_be_collided = true) :
	board_x(board_x), 
	board_y(board_y),	
	can_be_broken(can_be_broken),
	can_be_collided(can_be_collided),
	bomberman_game(bomberman_game) {};
	
	virtual ~BoardObject(){};
	
// Private methods
	///none
// Public methods
	///none
};

#endif