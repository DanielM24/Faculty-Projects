#include "Agent.h"
#include "Ranger_Agent_Type_4.h"
#include <fstream>

static std::ifstream file("Nume_Ranger.in");
Ranger_Agent_Type_4::Ranger_Agent_Type_4()
{
	file >> name;
	id = 4;
	health = 75;
	damage = 10;
	defence = 5;
	movement = 3;
	skill = 2;
}


Ranger_Agent_Type_4::~Ranger_Agent_Type_4()
{
}
