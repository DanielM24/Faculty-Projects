#pragma once

#include "Game_Mode.h"
#include "Agent.h"
#include "Spy_Agent_Type_1.h"
#include "Commando_Agent_Type_2.h"
#include "Hitman_Agent_Type_3.h"
#include "Ranger_Agent_Type_4.h"
#include "Medic_Agent_Type_5.h"
#include "Battle.h"
#include "Items.h"

#include<iostream>
#include<vector>
#include<conio.h>
#include<utility>
#include<time.h>

#define VAR

using namespace std; 

void Set_number_of_Agents(int agents);		//Setter pentru numarul total de agenti alocati pe harta

static int Get_number_of_Agents()			//Getter pentru numarul total de agenti alocati pe harta		
{
	return Agent::number_of_agents;
}

void Set_number_of_items(int x);			//Setter pentru numarul total de obiecte

static int Get_number_of_items()			//Getter pentru numarul total de obiecte
{
	return Items::number_of_items;
}

void Spawn_Items(std::string &amount)		// Functie pentru a alege cat de multe iteme dorim sa avem pe harta
{
	cout << "Cat de multe obiecte doriti sa fie pe harta? \n";
	cout << "R: ( Few || Many ) ";
	do
	{
		cin >> amount;
		if (amount != "Few" && amount != "Many")
			cout << "Mai introduceti inca o data optiunea: \n";
	} while (amount != "Few" && amount != "Many");
}

void Number_of_Items(std::string amount_items, int &number_of_items, Game_Mode &obj)	// Determinarea numarului de iteme ce vor fi pe harta
{
	if (amount_items == "Few")
	{
		number_of_items = (obj.get_Length() * obj.get_Width()) / 5;						// Daca ne dorim putine iteme
	}
	else
	{
		number_of_items = (obj.get_Length() * obj.get_Width()) / 2;						// Daca ne dorim multe iteme
	}
	Set_number_of_items(number_of_items);												// Stabilim numarul de iteme
}

void Array_of_Items(int &number_of_items, std::vector<Items*>&items)					// Introducem itemele ce vor fi spawnate pe harta intr un vector
{
	srand((int)time(0));
	int i;
	for (i = 0; i < number_of_items; i++)
	{
		int random = 6 + (rand() % 10);		// Alegem random itemele ( alegem un numar de la 6 la 15 - conform id-urilor itemelor)
		switch (random)
		{
		case 6:
		{
			Knife *knife = new Knife();
			items.push_back(knife);
			break;
		}
		case 7:
		{
			Pocket_Knife *pknife = new Pocket_Knife();
			items.push_back(pknife);
			break;
		}
		case 8:
		{
			Silencer *pistol = new Silencer();
			items.push_back(pistol);
			break;

		}
		case 9:
		{
			AK47 *rifle = new AK47();
			items.push_back(rifle);
			break;
		}
		case 10:
		{
			AWP *sniper = new AWP();
			items.push_back(sniper);
			break;
		}
		case 11:
		{
			Nova_Shotgun *shotgun = new Nova_Shotgun();
			items.push_back(shotgun);
			break;
		}
		case 12:
		{
			Medic_Kit *kit = new Medic_Kit();
			items.push_back(kit);
			break;
		}
		case 13:
		{
			Kevlar_Vest *vest = new Kevlar_Vest();
			items.push_back(vest);
			break;
		}
		case 14:
		{
			Grenade *grenade = new Grenade();
			items.push_back(grenade);
			break;
		}
		case 15:
		{
			Grenade_Molotov *molotov = new Grenade_Molotov();
			items.push_back(molotov);
			break;
		}
		}
	}
}

void Item_Placement(int &number_of_items, Game_Mode &obj, std::vector<Items*>&items)		// Spawnam iteme pe harta
{
	int i;
	for (i = 0; i < number_of_items; i++)
	{
		Set_position(obj, items[i]);
		items[i]->Position_on_map(obj);
	}
}

void Max_Agents(int &max_number_of_agents, Game_Mode &obj, int &number_of_items)			// Calculam numarul maxim de agenti pe care il putem avea 
{
	max_number_of_agents = (obj.get_Length()*obj.get_Width()) - number_of_items;
	if (max_number_of_agents > 500)															// Avem o limita de 500 de agenti pentru ca am introdus in total 500 de nume in fisierele cu nume de agenti, dar aceasta limita poate creste daca mai adaug nume
	{
		cout << "\n --------------------- ! ATENTIE ! --------------------- \n";
		cout << "Numarul maxim de nume alocate pentru agenti este 500, dar numarul maxim de agenti ce pot fi alocati este "<< max_number_of_agents << ". \n ";
		cout << "Va rugam sa alegeti un numar de agenti mai mic decat 500.";
	}
	else
	{
		cout << "\nNumarul maxim de agenti ce pot fi alocati este: " << max_number_of_agents<<" ;";

	}
}

void Agents_Placed(int &max_number_of_agents)		// Alegem cati agenti vrem sa avem pe harta
{
	cout << "\nNumarul de agenti alocati pe harta? Agenti: ";
	int agent;
	do
	{
		cin >> agent;
		if (agent <= 0 || agent >= max_number_of_agents || agent > 500)
		{
			cout << "\n --------------------- ! EROARE ! --------------------- \n";
			cout << "Nu se poate aloca numarul respectiv de agenti! \n Incearca din nou : ";
		}
		if (agent == 1)
		{
			cout << "\n Jocul nu isi mai are rostul. \n";
			cout << "Aloca cel putin doi agenti. \n Incearca din nou : ";
		}
		if (agent < 35 && agent > 1)				// In cerinta se preciza sa avem distribuiti minim 7 agenti de fiecare tip pe harta
		{
			cout << "\n Trebuie sa aloci minim 7 agenti de fiecare tip! (Min 35) \n ";
			cout << "Incearca din nou : ";
		}
	} while (agent > max_number_of_agents || agent >= 501 || agent < 35);
	Set_number_of_Agents(agent);
}

void Types_of_Agents(int &number_spy, int &number_commando, int &number_hitman, int &number_ranger, int&number_medic)
// Akegem random cati agenti din fiecare categorie vom avea pe harta
{
	srand((int)time(0));
	// Alegem numarul de agenti random dar tinem cont ca trebuie sa avem minim 7 agenti de fiecare categorie
	number_spy = (rand() % (Get_number_of_Agents() - 34)) + 7;
	number_commando = (rand() % (Get_number_of_Agents() - number_spy - 27)) + 7;
	number_hitman = (rand() % (Get_number_of_Agents() - number_spy - number_commando - 20)) + 7;
	number_ranger = (rand() % (Get_number_of_Agents() - number_spy - number_commando - number_hitman - 13)) + 7;
	number_medic = (rand() % (Get_number_of_Agents() - number_spy - number_commando - number_hitman - number_ranger - 6)) + 7;
	
	cout << "\n Au fost alesi aleator: \n";
	cout << number_spy << " -> Spioni; \n";
	cout << number_commando << " -> Soldati Commando; \n";
	cout << number_hitman << " -> Hitmen; \n";
	cout << number_ranger << " -> Lunetisti; \n";
	cout << number_medic << " -> Medici; \n";
}

void Array_of_Agents(int number_spy, int number_commando, int number_hitman, int number_ranger, std::vector<Agent*> &agents)
// Introducem agentii intr-un vector
{
	int counter;
	counter = 0;
		while (counter < number_spy)
		{
			counter++;
			Spy_Agent_Type_1 *spy = new Spy_Agent_Type_1;
			agents.push_back(spy);
		}
		while (counter < (number_spy + number_commando))
		{
			counter++;
			Commando_Agent_Type_2 *commando = new Commando_Agent_Type_2;
			agents.push_back(commando);
		}
		while (counter < (number_spy + number_commando + number_hitman))
		{
			counter++;
			Hitman_Agent_Type_3 *hitman = new Hitman_Agent_Type_3;
			agents.push_back(hitman);
		}
		while (counter < (number_spy + number_commando + number_hitman + number_ranger))
		{
			counter++;
			Ranger_Agent_Type_4 *ranger = new Ranger_Agent_Type_4;
			agents.push_back(ranger);
		}
		while (counter < Get_number_of_Agents())
		{
			counter++;
			Medic_Agent_Type_5 *medic = new Medic_Agent_Type_5;
			agents.push_back(medic);
		}	
}

void Agent_Placement(Game_Mode& obj, Agent*agent)			// Aseaza agentul pe harta
{
	int **map = obj.Get_the_map();

	std::pair<int, int> position = agent->Get_position();

	map[position.first][position.second] = agent->getId();
}

void Agent_Repartition(Game_Mode& obj, std::vector<Agent*> &vector, int number_of_agents)	// Asezam fiecare agent din vector pe harta
{
	int i;
	for (i = 0; i < number_of_agents; i++)
	{
		Set_position(obj, vector[i]);
		Agent_Placement(obj, vector[i]);
	}
}

// Actiuni realizare de agenti: 
void Agent_Actions(std::vector<Agent*> &agents, Game_Mode &obj, int &round, std::vector<Items*> &items)
{
	int i;
	for (i = 0; i < Get_number_of_Agents(); i++)
	{
		if (agents[i]->getHealth() > 0)			// Daca agentul este in viata, acesta se poate deplasa
		{
			agents[i]->Moving_Agent(obj, agents, items, round);
			Agent_Placement(obj, agents[i]);
			if (agents[i]->getHealth() <= 0)	// Daca agentul a murit atunci il scoatem din vector
			{
				agents.erase(agents.begin() + i);
				Set_number_of_Agents(Get_number_of_Agents() - 1);
				i--;
			}
		}
		else
		{
			agents.erase(agents.begin() + i);	// Daca agentul a murit atunci il scoatem din vector
			Set_number_of_Agents(Get_number_of_Agents() - 1);
			i--;
		}
	}
}

// Detalii despre desfasurarea unei runde
void Round_Details(int &round, std::vector<Agent*> agents, Game_Mode &obj)
{
	if (Get_number_of_Agents() > 1 && (obj.get_Round() == round || round == -2))
	{
		cout << "\n Agenti ramasi in viata: " << Get_number_of_Agents() << " ;\n";
		cout << "Runda curenta: " << obj.get_Round() << " ; \n";
		cout << obj << "\n";
	}
	else
		if (Get_number_of_Agents() == 1)
		{
			cout << "\n ----------------- ! SFARSIT DE JOC ! ----------------- \n";
			cout << "Durata Jocului: " << obj.get_Round() << " runde; \n";
			if (obj.get_Round() < round)	// Daca am cerut sa vedem o runda care nu exista pentru ca jocul s-a terminat mai repede
			{
				std::cout << "Jocul nu a avut " << round<<" runde. \n"; 
			}
			cout << "Durata Jocului: " << obj.get_Round() << " runde; \n";
			cout << "Agentul care a supravietuit este: " << agents[0]->Get_Name()<<". \n";
			
			switch (agents[0]->getId())
			{
			case 1:
			{
				cout << "Agentul este spion si a ramas cu " << agents[0]->getHealth() << " viata";
				break;
			}
			case 2:
			{
				cout << "Agentul este commando si a ramas cu " << agents[0]->getHealth() << " viata";
				break;
			}
			case 3:
			{
				cout << "Agentul este hitman si a ramas cu " << agents[0]->getHealth() << " viata";
				break;
			}
			case 4:
			{
				cout << "Agentul este lunetist si a ramas cu " << agents[0]->getHealth() << " viata";
				break;
			}
			case 5:
			{
				cout << "Agentul este medic si a ramas cu " << agents[0]->getHealth() << " viata";
				break;
			}
			}

			std::vector<Items*>items;
			items = agents[0]->Get_items();

			if (!items.empty())
			{
				int i;
				cout << "\n De asemenea, agentul avea asupra sa itemele: \n";
				for (i = 0; i < items.size(); i++)
				{
					cout << i+1 << ". " << items[i]->Get_name() << "\n";
				}

				cout << "Iteme nedescoperite: " << Get_number_of_items() << " ; \n";
	
			}

			cout << " Harta la final: \n";
			cout << obj;
		}
}

// Daca vrem sa sarim la o anumita runda
void Specific_Round_Details(bool &flag1, int &previous_round, int &current_round, Game_Mode &obj, bool &flag2)
{
	if (flag1 && obj.get_Round() - 1 == current_round)
	{
		cout << "\nDoriti sa vedeti o runda anume? ( Da / Nu ) : ";
		std::string answer;
		do
		{
			cin >> answer;
			if (answer != "Da" && answer != "Nu")
			{
				cout << "\n Raspuns necorespunzator. Variante: Da / Nu \n";
			}
		} while (answer != "Da" && answer != "Nu");

		if (answer == "Da")
		{
			flag1 = true;
			cout << "Runda pe care vreti sa o analizati: \n";
			do 
			{
				cin >> current_round;
				if (current_round < 0)
				{
					cout << "\n --------------------- ! EROARE ! --------------------- \n";
					cout << "Runda invalida! \n Introduceti o alta valoare : ";
				}
				else
					if (current_round == 0 && flag2)
					{
						cout << "\n --------------------- ! ATENTIE ! --------------------- \n";
						cout << "Runda initiala este deja afisata! \n Introduceti o alta valoare : ";
					}
				else
					if (current_round <= previous_round)
					{
						cout << "\n --------------------- ! ATENTIE ! --------------------- \n";
						cout << "Runda introdusa nu poate sa fie mai mica sau egala decat runda aleasa anterior (Runda : " << previous_round << " ); \n"<<"Introduceti o alta valoare : ";
					}	
			} while (current_round <= previous_round || current_round <= 0);
			previous_round = current_round;
			flag2 = false;
			}
		else
		{
			flag1 = false;
			current_round = -2;
		}
	}
}
// Initializarea jocului
void Game_Initialisation(std::vector<Agent*> &agents, std::vector<Items*> &items, Game_Mode &obj)
{
	std::string spawned_items = "";
	//  Cate iteme dorim sa avem pe harta
	Spawn_Items( VAR spawned_items);

	int number_of_items = 0;
	// Calculam numarul de iteme ce vor fi pe harta
	Number_of_Items(spawned_items, VAR number_of_items, obj);
	// Introducem itemele intr-un vector
	Array_of_Items(number_of_items, VAR items);
	// Punem itemele random pe harat
	Item_Placement(number_of_items, obj, items);

	int max_number_of_agents = 0;
	// Calculam numarul maxim de agenti pe care il putem avea pe harta
	Max_Agents( VAR max_number_of_agents, obj, number_of_items);
	// Alegem numarul de agenti pe care il vom avea pe harta
	Agents_Placed(max_number_of_agents);

	int number_spy, number_commando, number_hitman, number_ranger, number_medic;
	number_spy = number_commando = number_hitman = number_ranger = number_medic = 0;
	// Stabilim cati agenti din fiecare categorie vom avea
	Types_of_Agents(VAR number_spy,VAR number_commando,VAR number_hitman,VAR number_ranger,VAR number_medic);
	// Introducem agentii intr-un vector
	Array_of_Agents(number_spy, number_commando, number_hitman, number_ranger, agents);
	// Stabilim o locatie pentru fiecare agent pe harta
	Agent_Repartition(obj, agents, Get_number_of_Agents());
	
	// Mesajul de start din consola:
	cout << "----------------- | RUNDA INITIALA | ----------------- \n \n";
	cout << "---------------------- | SEED | ---------------------- \n";
	cout << "Agenti: " << Get_number_of_Agents() << " ; \nIteme: " << number_of_items<<"\n";
	cout << obj;


}