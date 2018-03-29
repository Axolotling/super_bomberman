#ifndef BOARD_H
#define BOARD_H
#include<map>
#include<set>
#include<assert.h>
#include"Rock.h"
#include"Crate.h"
#include"Player.h"
#include<time.h>
using namespace std;

class BoardObject; 

class Board
{
public:
	//losowo generowana mapa(podac liczbe graczy)
	Board(BombermanGame* bomberman_game,int n_players)
	{
		this->bomberman_game = bomberman_game;
		this->board_width = 30; //aktualnie tylko stosunek 3:2 ma sens, inne nie dzia³aja poprawnie
		this->board_height = 20;
		generating_map(); 
		assert(n_players != 0);//sprawdzenie liczby graczy i ich dodawanie
		add_player(1, 1); 
		if (n_players > 1)add_player(this->board_width - 2, this->board_height - 2);
		if (n_players > 2)add_player(this->board_width - 2, 1);
		if (n_players > 3)add_player(1, this->board_height - 2);
	}

	//zwraca iterator na poczatek mapy
	auto begin()
	{
		return board.begin();
	}

	//zwraca iterator na koniec mapy
	auto end()
	{
		return board.end();
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
	}

	//wstawia obiekt na pozycjê (nie sprawdza czy nadpisuje inny obiekt)
	void set_object(pair<int, int>position, BoardObject* object)
	{
		board[position] = object;
	}

	//virtualny destruktor
	virtual ~Board()
	{
		for (this->it = board.begin(); it != board.end(); it++)
			board[it->first]->~BoardObject();
		board.clear();
	}

private:
	map<pair<int, int>, BoardObject*>board;
	map<pair<int, int>, BoardObject*>::iterator it;
	BombermanGame* bomberman_game;
	int board_width;
	int board_height;

	//generowanie mapy
	void generating_map()
	{
		srand(time_t(0));

		//alokacja pamieci pomocniczej
		bool **tab = new bool*[this->board_height];
		for (int i = 0; i < this->board_height; i++)
			tab[i] = new bool[this->board_width];

		//przygotowanie obszaru pracy generatora
		for (int i = 0; i < this->board_height; i++)
			for (int j = 0; j < this->board_width; j++)
			{
				if (i<1 || j<1 || i>this->board_height - 2 || j>this->board_width - 2)tab[i][j] = false; //ramka
				else tab[i][j] = true; //obszar poza ramka jest dostepny
			}

		//generowanie wlasciwe
		for(int i=2;i<this->board_height-2;i++)
			for (int j = 2; j < this->board_width - 2; j++)
			{
				int k = i, p = j; //pomocnicze zapamietanie 
				if (tab[k-1][p-1]&&tab[k-1][p]&&tab[k-1][p+1]&&tab[k][p-1]&&tab[k][p]&&tab[k][p+1]&&tab[k+1][p-1]&&tab[k+1][p]&&tab[k+1][p+1]) //bezkolizyjnosc
				{
					tab[k][p] = false; //miejsce startu jest kamieniem
					int size = rand() % 4; //rozmiar obiektu w praktyce moze byc wiekszy, poniewaz dla ciekawszych map sprawdzane sa tylko 2 kierunki
					//2 kierunki starczaj¹, aby nie bylo redundancji obiektow, bo przechodzimy plansze wierszami!!
					//ponizszy while generuje kierunek ruchu magicznego olowka, ktorym wstawiamy obiekty polaczone z pojedynczych klockow.
					while (size&&((tab[k+1][p]&&k+1!=this->board_height-2)||(tab[k][p+1]&&p+1!=this->board_width-2)))
					{
						(rand()&1)?
							(tab[k + 1][p] && k+1 != this->board_height - 2)?
								(tab[++k][p] = false):
								(tab[k][++p] = false):
							(tab[k][p + 1] && p+1 != this->board_width - 2)?
								(tab[k][++p] = false):
								(tab[++k][p] = false);
						size--;
					}
				}
			}

		//dodanie kamieni
		for (int i = 0; i < this->board_height; i++)
			for (int j = 0; j < this->board_width; j++)
				if (!tab[i][j])
					set_object({ j,i }, new Rock(bomberman_game, j, i));

		//dodanie szkrzynek

		//dealokacja pamieci pomocniczej
		for (int i = 0; i < this->board_height; i++)delete[] tab[i];
		delete[] tab;
	}

	//dodanie gracza
	void add_player(int x, int y)
	{
		Player* new_player = new Player(bomberman_game, x, y);
		bomberman_game->players.push_front(new_player);
		set_object({x,y},new_player); 
	}
};
#endif