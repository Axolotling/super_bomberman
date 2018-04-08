#ifndef BOARD_H
#define BOARD_H
#include<map>
#include<set>
#include<assert.h>
#define _WINSOCKAPI_
#include<windows.h>
#include"Rock.h"
#include"Crate.h"
#include"Player.h"
#include<time.h>
#include <list>
#include <queue>
#include "LocalPlayer.h"
using namespace std;

class BoardObject;

class Board : public Displayable
{
public:
	//losowo generowana mapa(podac liczbe graczy)
	Board(int n_players, ActionLog *action_log, Communicator *communicator)
	{
		///this->bomberman_game = bomberman_game;
		this->board_width = 30; //aktualnie tylko stosunek 3:2 ma sens, inne nie dzia³aja poprawnie
		this->board_height = 20;
		generating_map();
		assert(n_players != 0);//sprawdzenie liczby graczy i ich dodawanie
		add_local_player(1, 1, 0, action_log, communicator);
		if (n_players > 1)
		{
			add_player(this->board_width - 2, this->board_height - 2, 0, communicator);
		}
		if (n_players > 2)
		{
			add_player(this->board_width - 2, 1, 2, communicator);
		}
		if (n_players > 3) {
			add_player(1, this->board_height - 2, 3, communicator);
		}
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
//usuwa element mapy korzystajac z klucza(pozycji)
	void key_erase(pair<int, int> position)
		{
		it = board.find(position);
		if (it != board.end())
			{
			board[position]->~BoardObject();
			board.erase(it);
			}
		//cout<<"elementu nie znaleziono\n";
		}
 
	//usuwa element mapy korzystaj¹c z wartoœci(adresu obiektu)
	void value_erase(BoardObject* object)
		{
		for(it=board.begin();it!=board.end();it++)
			if (it->second == object)
				{
				board[it->first]->~BoardObject();
				board.erase(it);
				return;
				}
		//cout<<"elementu nie znaleziono\n";
		}


	//virtualny destruktor
	virtual ~Board()
	{
		for (this->it = board.begin(); it != board.end(); it++)
			board[it->first]->~BoardObject();
		board.clear();
	}

	void update(sf::Time delta_time) override
	{
		for (Player *player : players)
		{
			if (Displayable *displayable = dynamic_cast<Displayable*>(player))
			{
				displayable->update(delta_time);
			}
		}
		for (auto it = begin(); it != end(); it++)
			if (it->second != nullptr)
			{
				if (Displayable *displayable = dynamic_cast<Displayable*>(it->second))
				{
					displayable->update(delta_time);
				}
			}
		delete_sheduled_objects();
	};

	void display(sf::RenderWindow* window) override
	{		
		for (auto it = begin(); it != end(); it++)
			if (it->second != nullptr)
			{
				if (Displayable *displayable = dynamic_cast<Displayable*>(it->second))
				{
					displayable->display(window);
				}
			}

		for (Player *player : players)
		{
			if (Displayable *displayable = dynamic_cast<Displayable*>(player))
			{
				displayable->display(window);
			}
		}
	};

	void shedule_for_deletion(BoardObject* board_object)
	{
		sheduled_for_deletion.push(board_object);
	}

private:
	map<pair<int, int>, BoardObject*>board;
	map<pair<int, int>, BoardObject*>::iterator it;
	//BombermanGame* bomberman_game;
	int board_width;
	int board_height;
	list<Player*> players;
	queue<BoardObject*> sheduled_for_deletion;

	void delete_sheduled_objects()
	{
		while (sheduled_for_deletion.size() != 0)
		{
			value_erase(sheduled_for_deletion.front());
			sheduled_for_deletion.pop();
		}
	}

	//generowanie mapy
	void generating_map()
	{
		//srand(time_t(0));

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
		for (int i = 2; i<this->board_height - 2; i++)
			for (int j = 2; j < this->board_width - 2; j++)
			{
				int k = i, p = j; //pomocnicze zapamietanie 
				if (tab[k - 1][p - 1] && tab[k - 1][p] && tab[k - 1][p + 1] && tab[k][p - 1] && tab[k][p] && tab[k][p + 1] && tab[k + 1][p - 1] && tab[k + 1][p] && tab[k + 1][p + 1]) //bezkolizyjnosc
				{
					tab[k][p] = false; //miejsce startu jest kamieniem
					int size = rand() % 4; //rozmiar obiektu w praktyce moze byc wiekszy, poniewaz dla ciekawszych map sprawdzane sa tylko 2 kierunki
										   //2 kierunki starczaj¹, aby nie bylo redundancji obiektow, bo przechodzimy plansze wierszami!!
										   //ponizszy while generuje kierunek ruchu magicznego olowka, ktorym wstawiamy obiekty polaczone z pojedynczych klockow.
					while (size && ((tab[k + 1][p] && k + 1 != this->board_height - 2) || (tab[k][p + 1] && p + 1 != this->board_width - 2)))
					{
						(rand() & 1) ?
							(tab[k + 1][p] && k + 1 != this->board_height - 2) ?
							(tab[++k][p] = false) :
							(tab[k][++p] = false) :
							(tab[k][p + 1] && p + 1 != this->board_width - 2) ?
							(tab[k][++p] = false) :
							(tab[++k][p] = false);
						size--;
					}
				}
			}

		double ballast = 12;

		//dodanie kamieni
		for (int i = 0; i < this->board_height; i++)
			for (int j = 0; j < this->board_width; j++)
				if (!tab[i][j])
				{
					ballast++; //obciazenie planszy
					set_object({ j,i }, new Rock(this, j, i));
				}

		//wykluczenie pol pod graczami i zapewnienie im poprawnego ruchu
		//zalozenie ze na kazdej mapie gracze maja te same pozycje wzgledem rozmiaru mapy
		tab[1][1] = tab[2][1] = tab[1][2] = 0;
		tab[this->board_height - 2][this->board_width - 2] = tab[this->board_height - 2][this->board_width - 3] = tab[this->board_height - 3][this->board_width - 2] = 0;
		tab[1][this->board_width - 2] = tab[2][this->board_width - 2] = tab[1][this->board_width - 3] = 0;
		tab[this->board_height - 2][1] = tab[this->board_height - 3][1] = tab[this->board_height - 2][2] = 0;

		//cout << "Skrzynki tu beda dodawane" << endl;

		//dodanie tylu skrzynek aby zapelnienie calej planszy wynosilo okreslony % calosci mapy
		while (ballast / double(this->board_height*this->board_width) < 0.7)
		{
			int x = rand() % this->board_width;
			int y = rand() % this->board_height;
			if (tab[y][x])
			{
				set_object({ x,y }, new Crate(this, x, y));
				tab[y][x] = 0;
				ballast++;
			}
		}

		//cout << "Skrzynki tu byly dodawane" << endl;

		//dealokacja pamieci pomocniczej
		for (int i = 0; i < this->board_height; i++)delete[] tab[i];
		delete[] tab;
	}

	//dodanie gracza
	void add_player(int x, int y, int id, Communicator *communicator)
	{
		Player* new_player = new Player(this, x, y, id, communicator);
		players.push_front(new_player);
		//set_object({ x,y }, new_player);
	}

	//dodanie gracza
	void add_local_player(int x, int y, int id, ActionLog *action_log, Communicator *communicator)
	{
		Player* new_player = new LocalPlayer(this, x, y, id, action_log, communicator);
		players.push_front(new_player);
		//set_object({ x,y }, new_player);
	}
};
#endif