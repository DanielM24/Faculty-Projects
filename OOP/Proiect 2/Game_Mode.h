#pragma once

#include <iostream>

class Game_Mode
{
private:
	int **map;  // Harta pe care se va desfasura jocul
	int length; // Lungimea hartii
	int width;  // Latimea hartii
	int round;  // Contor pentru rundele desfasurate
public:
	Game_Mode() : length(0), width(0), round(0), map(NULL) {}; // Constructor cu lista de initializare
	~Game_Mode();											   // Destructor

	friend std::istream& operator>>(std::istream&, Game_Mode&);		  // Supraincarcare operatorul de citire a hartii >>
	friend std::ostream& operator<<(std::ostream&, const Game_Mode&); // Supraincarcare operatorul de afisare a hartii <<

	int**Get_the_map();			// Getter pentru harta
	
	int get_Length();			// Getter pentru lungimea hartii
	int get_Width();			// Getter pentru latimea hartii

	int get_Round();			// Getter pentru obtinerea rundei
	void set_Round(int x);		// Setter pentru runda

	friend void StartGame(Game_Mode &obj);	// Functie pentru a incepe jocul
};

