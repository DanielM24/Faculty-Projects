#include<iostream>
#include"Game_Mode.h"
using namespace std;

int main()
{
	Game_Mode Map;
	cin >> Map;	// Introducem datele despre harta

	StartGame(Map); // Incepem Survival-Game
	system("pause");

	return 0;
}