#include "Game_Mode.h"
#include "Agent.h"
#include "Spy_Agent_Type_1.h"
#include "Commando_Agent_Type_2.h"
#include "Hitman_Agent_Type_3.h"
#include "Ranger_Agent_Type_4.h"
#include "Medic_Agent_Type_5.h"
#include "Menu.h"

#include <iostream>

using namespace std;

Game_Mode::~Game_Mode()	// Destructor harta de joc
{
	int i;
	for (i = 0; i < length; i++)
		delete[] map[i];
	delete[] map;
}

int ** Game_Mode::Get_the_map()
{
	return map;
}

int Game_Mode::get_Length()
{
	return length;
}
int Game_Mode::get_Width()
{
	return width;
}

int Game_Mode::get_Round()
{
	return this->round;
}
void Game_Mode::set_Round(int x)
{
	this->round = x;
}

void StartGame(Game_Mode &obj)
{
	std::vector<Agent*>agents;
	std::vector<Items*>items;

	Game_Initialisation(agents, items, obj);	// Initializam jocul

	bool flag1 = true;
	bool flag2 = true;
	int previous_round = -2;
	int round = -1;
	
	while (Get_number_of_Agents() > 1)
	{
		if (flag1)
			Specific_Round_Details( VAR flag1, VAR previous_round, VAR round, obj, VAR flag2);
			
		Agent_Actions(agents, obj, round, items);
		
		Round_Details(round, agents, obj);

		obj.set_Round(obj.get_Round() + 1);
	}

}

std::istream& operator>>(std::istream& is, Game_Mode&obj)
{
	int i, j;
	cout << "Introduceti lungimea hartii (Min 15) : \n";
	do {
		is >> obj.length;
		if (obj.length < 15)
		{
			cout << "\nLungimea hartii trebuie sa fie minim 15. Introduceti o noua valoare: ";
			is >> obj.length;
		}
	} while (obj.length < 15);
	cout << "Introduceti latimea hartii (Min 15) : \n";
	do {
		is >> obj.width;
		if (obj.width < 15)
		{
			cout << "\nLatimea hartii trebuie sa fie minim 15. Introduceti o noua valoare: ";
			is >> obj.width;
		}
	} while (obj.width < 15);

	obj.map = new int*[obj.length];

	for (i = 0; i < obj.length; i++)
		obj.map[i] = new int[obj.width];

	for (i = 0; i < obj.length; i++)
		for (j = 0; j < obj.width; j++)
			obj.map[i][j] = 0;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Game_Mode &obj)
{
	int i, j;
	cout << "\n";
	os << "Lungimea hartii este: " << obj.length;
	cout << "\n";
	os << "Latimea hartii este: " << obj.width;
	cout << "\n";
	for (i = 0; i < obj.length; i++)
	{
		for (j = 0; j < obj.width; j++)
			os << obj.map[i][j] << "  ";
		os << "\n";
	}
	return os;
}
