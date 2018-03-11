#pragma once
#include "BoardObject.h"


class BombermanGame
{
	// Public definitions
public:
	// Private fields
private:
	BoardObject ***board; //board[x][y]->motoda() pozwala wywo³aæ metodê obiektu

	// Public fields
public:
	const int board_width;
	const int board_height;

	// Constructors and destructors
	BombermanGame(const int &board_width, const int &board_height) :board_width(board_width), board_height(board_height)
	{
		board = new BoardObject**[board_width];
		for (int i = 0; i < board_width; i++)
		{
			board[i] = new BoardObject*[board_height];
			board[i] = nullptr;
		}
	};
	~BombermanGame() = default;
	// Private methods

	// Public methods

};



// Public definitions
// Private fields
// Public fields
// Constructors and destructors
// Private methods
// Public methods