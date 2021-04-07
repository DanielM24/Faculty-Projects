#include "Agent.h"
#include "Spy_Agent_Type_1.h"
#include <fstream>

static std::ifstream file("Nume_Spy.in");
Spy_Agent_Type_1::Spy_Agent_Type_1()
{
	file >> name;
	id = 1;
	health = 75;
	damage = 30;
	defence = 10;
	movement = 2;
	skill = 3;
}

Spy_Agent_Type_1::~Spy_Agent_Type_1()
{
}
