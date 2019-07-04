#pragma once
class Agent;
class Game_Mode;

class Battle
{
public:
	static void Fight(Agent* agent1, Agent* agent2, int round, Game_Mode &obj); // Functia ce permite confruntarea dintre 2 agenti
	static bool Attack(Agent* agent1, Agent* agent2, int round, Game_Mode &obj); // Functia ce indica atacul agentului 1 asupra agentului 2 si daca agentul 2 a pierdut confruntarea
	~Battle() {}
};

