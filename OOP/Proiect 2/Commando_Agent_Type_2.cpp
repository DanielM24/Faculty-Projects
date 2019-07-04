#include "Agent.h"
#include "Commando_Agent_Type_2.h"
#include <fstream>

static std::ifstream file("Nume_Commando.in");
Commando_Agent_Type_2::Commando_Agent_Type_2()
{
	file >> name;
	id = 2;
	health = 200;
	damage = 45;
	defence = 20;
	movement = 1;
	skill = 1;
}


Commando_Agent_Type_2::~Commando_Agent_Type_2()
{
}
