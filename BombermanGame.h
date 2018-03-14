#ifndef BOMBERMANGAME_H
#define BOMBERMANGAME_H



#include "Player.h"


class BombermanGame
{
// Public definitions
public:
	///none

// Private fields
private:
	Player* add_player(int x, int y)
	{
		Player* new_player = new Player(this, x, y);
		players.push_front(new_player);
		board[x][y] = new_player;
		return new_player;
	}

// Public fields
public:
	// plansza - zawiera informacje o tym co znajduje siê w ka¿dym miejscu planszy
	BoardObject ***board; //board[x][y]->metoda() pozwala wywo³aæ metodê obiektu
	// wymiary siatki planszy gry
	const int board_width, board_height;
	std::list<Player*> players;
	Player* local_player;

	int publiczne_cos = 2;

// Constructors and destructors
	BombermanGame(const int &board_width, const int &board_height) :board_width(board_width), board_height(board_height)
	{
		board = new BoardObject**[board_width];
		for (int i = 0; i < board_width; i++)
		{
			board[i] = new BoardObject*[board_height];
			for (int j = 0; j < board_height; j++)
			{
				board[i][j] = nullptr;
			}
		}
		local_player = add_player(0, 0);
	};

	~BombermanGame() = default;

// Private methods
	///none
// Public methods

	// g³ówna pêtla gry
	void loop()
	{
		
		



	}
};



// Public definitions
// Private fields
// Public fields
// Constructors and destructors
// Private methods
// Public methods

#endif