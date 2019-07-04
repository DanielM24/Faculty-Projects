#pragma once
#include <iostream>
#include <string>
#include <vector>

class Game_Mode;
class Items;

class Agent
{
protected:
	// Fiecare agent in parte va fi caracterizat printr-un nume si un id care arata tipul agentului
	std::string name;	
	int id;
	// Fiecare agent va avea ca atribute: Viata, Atac, Aparare, Mobilitate si Skill
    int health;
	int damage;
	int defence;
	int movement;
	int skill; 
	// De asemenea, fiecare agent va avea propriile coordonate pe harta si anumite iteme la indemana, daca le va gasi
	std::pair <int, int> position_on_map;
	std::vector<Items*> items_collected;

	static int number_of_agents; // Numarul de agenti

public:
	Agent() :health(0), damage(0), defence(0), movement(0), id(0) {}; // Constructor cu lista de initializare
	virtual ~Agent();	// Destructorul pentru clasa Agent

	void setHealth(int hp);	//Setter pentru viata unui agent
	int getHealth();		//Getter pentru viata unui agent

	void setDamage(int dmg);	//Setter pentru atacul unui agent
	int getDamage();			//Getter pentru atacul unui agent

	void setDefence(int def);	//Setter pentru apararea unui agent
	int getDefence();			//Getter pentru apararea unui agent

	void setMovement(int mov);	//Setter pentru mobilitatea unui agent
	int getMovement();			//Getter pentru mobilitatea unui agent

	void setSkill(int skl);		//Setter pentru skill-ul unui agent
	int getSkill();				//Getter pentru skill-ul unui anget

	void setId(int index);		//Setter pentru tipul de agent
	int getId();				//Getter pentru tipul de agent

	friend void Set_number_of_Agents(int agents);	 //Setter pentru numarul de agenti
	friend static int Get_number_of_Agents();		 //Getter pentru numarul de agenti
	
	friend void Set_position(Game_Mode& obj, Agent *agent); // Functie pentru pozitionarea unui agent pe harta
	
	void Set_position_x(int x);			// Setter pentru coordonata x a agentului
	void Set_position_y(int y);			// Setter pentru coordonata y a agentului
	std::pair<int, int> Get_position();	// Getter pentru pozitia agentului pe harta

	virtual std::string Get_Name();		// Getter nume agent
	std::vector<Items*> Get_items();	// Getter iteme pe care le detinea agentul

	void Moving_Agent(Game_Mode& obj, std::vector<Agent*> &vector, std::vector<Items*> &items, int round); // Functia pentru deplasarea agentului pe harta

};