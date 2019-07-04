#include "Agent.h"
#include "Medic_Agent_Type_5.h"
#include <fstream>

static std::ifstream file("Nume_Medic.in");
Medic_Agent_Type_5::Medic_Agent_Type_5()
{
	file >> name;
	id = 5;
	health = 200;
	damage = 10;
	defence = 5;
	movement = 3;
	skill = 1;
}


Medic_Agent_Type_5::~Medic_Agent_Type_5()
{
}
