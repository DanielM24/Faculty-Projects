#include "Agent.h"
#include "Hitman_Agent_Type_3.h"
#include <fstream>

static std::ifstream file("Nume_Hitman.in");
Hitman_Agent_Type_3::Hitman_Agent_Type_3()
{
	file >> name;
	id = 3;
	health = 150;
	damage = 45;
	defence = 20;
	movement = 2;
	skill = 2;
}


Hitman_Agent_Type_3::~Hitman_Agent_Type_3()
{
}
