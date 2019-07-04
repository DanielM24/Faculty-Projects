#include "Battle.h"
#include "Agent.h"
#include "Spy_Agent_Type_1.h"
#include "Commando_Agent_Type_2.h"
#include "Hitman_Agent_Type_3.h"
#include "Ranger_Agent_Type_4.h"
#include "Medic_Agent_Type_5.h"
#include "Game_Mode.h"

#include<iostream>
#include<ctime>

using namespace std;

void Battle::Fight(Agent * agent1, Agent * agent2, int round, Game_Mode & obj)
{
	if (round == obj.get_Round() || round == -2)
	{
		cout << "\n CONFRUNTARE intre " << agent1->Get_Name();
		switch (agent1->getId())
		{
		case 1:
		{
			cout << " care este spion si ";
			break;
		}
		case 2:
		{
			cout << " care este commando si ";
			break;
		}
		case 3:
		{
			cout << " care este hitman si ";
			break;
		}
		case 4:
		{
			cout << " care este lunetist si ";
			break;
		}
		case 5:
		{
			cout << " care este medic si ";
			break;
		}
		}
		cout << agent2->Get_Name();
		switch (agent2->getId())
		{
		case 1:
		{
			cout << " care este spion .";
			break;
		}
		case 2:
		{
			cout << " care este commando .";
			break;
		}
		case 3:
		{
			cout << " care este hitman .";
			break;
		}
		case 4:
		{
			cout << " care este lunetist .";
			break;
		}
		case 5:
		{
			cout << " care este medic .";
			break;
		}
		}
	}

	bool fight = false;
	do 
	{
		fight = Attack(agent1, agent2, round, obj);
		if (fight)
			break;
		fight = Attack(agent2, agent1, round, obj);
	} while (agent1->getHealth() > 0 && agent2->getHealth() > 0);
}

bool Battle::Attack(Agent * agent1, Agent * agent2, int round, Game_Mode & obj)
{
	srand((int)time(0));

	int attack = rand() % agent1->getDamage() +10;
	int defence = rand() % agent2->getDefence()+5;

	int health = agent2->getHealth();

	int damage = (attack * agent1->getSkill()) - (defence * agent2->getSkill());
	if (damage < 0)
		damage = 0;

	health = health - damage;
	if (health <= 0)
	{
		if (round == obj.get_Round() || round == -2)
		{
			cout << "\n" << agent1->Get_Name() << " il infrange pe " << agent2->Get_Name() << "; \n";
			cout << "Agentul " << agent1->Get_Name() << " a ramas cu " << agent1->getHealth() << " viata; \n ";
		}
		agent2->setHealth(health);
		return true;
	}
	agent2->setHealth(health);
	return false;
}