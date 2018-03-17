#ifndef BOARD_H
#define BOARD_H
#include<map>
#include<set>
#include<tuple>
using namespace std;

class BoardObject;

class Board
{
public:
	Board() //w konstruktorze sobie wygenerujemy jakas mapke
		{
		this->board_width = 30;
		this->board_height = 30;
		}
	pair<int, int>get_map_size() //zwraca parê (szerokosc,wysokosc) rozmiaru wygenerowanej planszy
		{
		return make_pair(this->board_width,this->board_height);
		}
	BoardObject* get_object(pair<int, int>position) //zwraca wskaŸnik na obiekt z danej pozycji(null w przypadku, gdy nie ma tam obiektu)
		{
		auto element = board.find(position);
		if (element != board.end())
			return element->second;
		else
			return nullptr;
		}
	void set_object(pair<int, int>position, BoardObject* object) //wstawia obiekt object na pozycjê position(nie sprawdza czy nadpisuje inny obiekt)
		{
		board[position] = object;
		}
	virtual ~Board()
		{
		board.clear();
		}
private:
	map<pair<int, int>, BoardObject*>board; //mapa na obiekty z kluczem, który jest krotk¹ przechowuj¹ca pozycje, ¿eby szybciej sprawdzaæ.
	map<pair<int, int>, BoardObject*>::iterator it; //iterator do chodzenia po mapie;
	int board_width;
	int board_height;
	float fRand(float fMin, float fMax)
		{
		float f= (float) rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
		}
	int iRand(int iMin, int iMax)
		{
		int i = (int)rand() / RAND_MAX;
		return iMin + i * (iMax - iMin);
		}
};
#endif