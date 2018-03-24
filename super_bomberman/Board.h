#ifndef BOARD_H
#define BOARD_H
#include<map>
#include<set>
#include<assert.h>
#include"Rock.h"
#include"Crate.h"
#include"Player.h"
using namespace std;

class BoardObject;

class Board// : public Displayable
{
public:
	//losowo generowana mapa(podac liczbe graczy)
	Board(BombermanGame* bomberman_game,int n_players)
	{
		this->bomberman_game = bomberman_game;
		this->board_width = 15; //aktualnie tylko stosunek 3:2 ma sens, inne nie dzia³aja poprawnie
		this->board_height = 10;
		//dodanie stalej kamiennej ramki
		for (int i = 0; i < this->board_width; i++)
		{
			set_object({ 0,i }, new Rock(bomberman_game, 0, i));
			set_object({ this->board_width - 1,i }, new Rock(bomberman_game, this->board_width - 1, i));
			if (i != 0 && i != this->board_width - 1)
			{
				set_object({ i,0 }, new Rock(bomberman_game, i, 0));
				set_object({ i,this->board_height - 1 }, new Rock(bomberman_game, i, this->board_height - 1));
			}
		}
		//sprawdzenie liczby graczy
		assert(n_players!=0);
		add_player(1,1); 
		if(n_players>1)add_player(this->board_width - 2, this->board_height - 2);
		if(n_players>2)add_player(this->board_width - 2,1);
		if(n_players>3)add_player(1, this->board_height - 2);
	}
	//zwraca parê (szerokosc,wysokosc) rozmiaru wygenerowanej planszy
	pair<int, int>get_map_size()
	{
		return make_pair(this->board_width, this->board_height);
	}
	//zwraca wskaŸnik na obiekt z danej pozycji(null w przypadku, gdy nie istnieje tam obiekt)
	BoardObject* get_object(pair<int, int>position)
	{
		auto element = board.find(position);
		if (element != board.end())
			return element->second;
		else
			return nullptr;

		int *tab = new int[10];
		for (int i = 0; i < 10; i++)
		{
			cout << tab[i];

		}
	}
	//wstawia obiekt object na pozycjê position(nie sprawdza czy nadpisuje inny obiekt)
	void set_object(pair<int, int>position, BoardObject* object)
	{
		board[position] = object;
	}

	virtual ~Board()
	{
		for (this->it = board.begin(); it != board.end(); it++)
			board[it->first]->~BoardObject();
		board.clear();
	}

private:
	//mapa na obiekty z kluczem, który jest krotk¹ przechowuj¹ca pozycje, ¿eby szybciej sprawdzaæ.
	map<pair<int, int>, BoardObject*>board;
	//iterator do chodzenia po mapie;
	map<pair<int, int>, BoardObject*>::iterator it;
	//wskaznik na gre
	BombermanGame* bomberman_game;

	int board_width;
	int board_height;

	void add_player(int x, int y)
	{
		Player* new_player = new Player(bomberman_game, x, y);
		bomberman_game->players.push_front(new_player);
		set_object({x,y},new_player);
	}

	float fRand(float fMin, float fMax)
	{
		float f = (float)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

	int iRand(int iMin, int iMax)
	{
		int i = (int)rand() / RAND_MAX;
		return iMin + i * (iMax - iMin);
	}
};
#endif