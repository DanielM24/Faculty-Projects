#include "Agent.h"
#include "Game_Mode.h"
#include "Battle.h"
#include "Items.h"
#include <vector>
#include <ctime>

using namespace std;

int Agent::number_of_agents = 0;

Agent::~Agent()
{
	health = 0;
	damage = 0;
	defence = 0;
	movement = 0;
	id = 0;
}

inline void Set_number_of_items(int x)
{
	Items::number_of_items = x;
}
static int Get_number_of_items()
{
	return Items::number_of_items;
}

void Agent::setHealth(int hp)
{
	this->health = hp;
}
int Agent::getHealth()
{
	return this->health;
}

void Agent::setDamage(int dmg)
{
	this->damage = dmg;
}
int Agent::getDamage()
{
	return this->damage;
}

void Agent::setDefence(int def)
{
	this->defence = def;
}
int Agent::getDefence()
{
	return this->defence;
}

void Agent::setMovement(int mov)
{
	this->movement = mov;
}
int Agent::getMovement()
{
	return this->movement;
}

void Agent::setSkill(int skl)
{
	this->skill = skl;
}
int Agent::getSkill()
{
	return this->skill;
}

void Agent::setId(int index)
{
	this->id = index;
}
int Agent::getId()
{
	return this->id;
}

void Agent::Set_position_x(int x)
{
	this->position_on_map.first = x;
}

void Agent::Set_position_y(int y)
{
	this->position_on_map.second = y;
}

std::pair<int, int> Agent::Get_position()
{
	return this->position_on_map;
}

std::string Agent::Get_Name()
{
	return this-> name;
}

std::vector<Items*> Agent::Get_items()
{
	return this->items_collected;
}

void Set_number_of_Agents(int agents)
{
	Agent::number_of_agents = agents;
}
static int Get_number_of_Agents()
{
	return Agent::number_of_agents;
}


// Pozitia fiecarui agent este aleasa intr-un mod aleatoriu
void Set_position(Game_Mode& obj, Agent *agent)
{
	srand((int)time(0));
	int **map = obj.Get_the_map();
	int x, y;
	do
	{
		x = rand() % obj.get_Length();
		y = rand() % obj.get_Width();
		agent->Set_position_x(x);
		agent->Set_position_y(y);
	} while (map[agent->position_on_map.first][agent->position_on_map.second] != 0);
}

// Alegem o noua pozitie a agentului si verificam daca gasim un item sau un agent
void Agent::Moving_Agent(Game_Mode&obj, std::vector<Agent*>&vector, std::vector<Items*> &items, int round)
{
	srand((int)time(0));
	int**map = obj.Get_the_map();
	int vertical_movement, orizontal_movement;

	int speed = this->movement;
	bool no_movement = true;
	bool case1, case2;
	case1 = false;
	case2 = false;

	if (this->position_on_map.first == 0)

	{
		vertical_movement = rand() % 75;
		case1 = true;
	}
	else 
		if (this->position_on_map.first == obj.get_Length() - 1)
		{
			vertical_movement = rand() % 8 + (-6);
			case1 = true;
		}

	if (this->position_on_map.second == 0)
	{
		orizontal_movement = rand() % 75;
		case2 = true;
	}
	else if (this->position_on_map.second == obj.get_Width() - 1)
	{
		orizontal_movement = rand() % 8 + (-6);
		case2 = true;
	}

	if (case1 && !case2)
		orizontal_movement = rand() % 8 + (-4);
	else if (case2 && !case1)
		vertical_movement = rand() % 8 + (-4);
	else if (!case1 && !case2)
	{
		vertical_movement = rand() % 8+ (-4);
		orizontal_movement = rand() % 8 + (-4);
	}


	int copy_position_first = this->position_on_map.first;
	int copy_position_second = this->position_on_map.second;

	if (vertical_movement > 0)
	{
		if (this->position_on_map.first + this->movement < obj.get_Length())
		{
			this->position_on_map.first += speed;
			no_movement = false;
		}

		else if (this->position_on_map.first != obj.get_Length() - 1)
		{
			this->position_on_map.first = obj.get_Length() - 1;
			no_movement = false;
		}
	}

	else if (vertical_movement < 0)
	{
		if (this->position_on_map.first - this->movement >= 0)
		{
			this->position_on_map.first -= speed;
			no_movement = false;
		}

		else  if (this->position_on_map.first != 0)
		{
			this->position_on_map.first = 0;
			no_movement = false;
		}
	}

	if (orizontal_movement > 0)
	{
		if (this->position_on_map.second + this->movement < obj.get_Width())
		{
			this->position_on_map.second += speed;
			no_movement = false;
		}

		else if (this->position_on_map.second != obj.get_Width() -1)
		{
			this->position_on_map.second = obj.get_Width() - 1;
			no_movement = false;
		}
	}
	else if (orizontal_movement < 0)
	{
		if (this->position_on_map.second - this->movement >= 0)
		{
			this->position_on_map.second -= speed;
			no_movement = false;
		}

		else if (this->position_on_map.second != 0)
		{
			this->position_on_map.second = 0;
			no_movement = false;
		}
	}

	if (no_movement && (obj.get_Round() == round || round == -2))
	{
		cout << "Agentul " << this->Get_Name();
		switch (this->getId())
		{
		case 1:
		{
			cout << "care este spion se afla pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "a ales sa ramana pe aceeasi pozitie. \n";
			break;
		}
		case 2:
		{
			cout << "care este commando se afla pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "a ales sa ramana pe aceeasi pozitie. \n";
			break;
		}
		case 3:
		{
			cout << "care este hitman se afla pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "a ales sa ramana pe aceeasi pozitie. \n";
			break;
		}
		case 4:
		{
			cout << "care este lunetist se afla pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "a ales sa ramana pe aceeasi pozitie. \n";
			break;
		}
		case 5:
		{
			cout << "care este medic se afla pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "a ales sa ramana pe aceeasi pozitie. \n";
			break;
		}
		}
	}
	else
	{
		if (obj.get_Round() == round || round == -2)
		{
			cout << "Agentul " << this->Get_Name();
			switch (this->getId())
			{
			case 1:
			{
				cout << "care este spion s-a miscat de pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "pe pozitia [ "<<this->position_on_map.first<<" ] [ "<<this->position_on_map.second<<" ] cu viteza "<<speed<<" ;\n";
				break;
			}
			case 2:
			{
				cout << "care este commando s-a miscat de pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "pe pozitia [ " << this->position_on_map.first << " ] [ " << this->position_on_map.second << " ] cu viteza " << speed << " ;\n";
				break;
			}
			case 3:
			{
				cout << "care este hitman s-a miscat de pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "pe pozitia [ " << this->position_on_map.first << " ] [ " << this->position_on_map.second << " ] cu viteza " << speed << " ;\n";
				break;
			}
			case 4:
			{
				cout << "care este lunetist s-a miscat de pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "pe pozitia [ " << this->position_on_map.first << " ] [ " << this->position_on_map.second << " ] cu viteza " << speed << " ;\n";
				break;
			}
			case 5:
			{
				cout << "care este medic s-a miscat de pe pozitia [ " << copy_position_first << " ] [ " << copy_position_second << " ] " << "pe pozitia [ " << this->position_on_map.first << " ] [ " << this->position_on_map.second << " ] cu viteza " << speed << " ;\n";
				break;
			}
			}
		}
		map[copy_position_first][copy_position_second] = 0;
	}
	// Daca am gasit pe aceasta pozitie un agent, atunci incepe o confruntare
	if ( map[this->position_on_map.first][this->position_on_map.second] < 6 && map[this->position_on_map.first][this->position_on_map.second] != 0)
	{
		for (int i = 0; i < Get_number_of_Agents(); i++)
		{
			if (vector[i]->health > 0 && vector[i]->name != this->name && vector[i]->position_on_map.first == this->position_on_map.first && vector[i]->position_on_map.second == this->position_on_map.second)
			{
				Battle::Fight(this, vector[i], round, obj);
			}
		}

	}
	// Daca am gasit pe aceasta pozitie un item, atunci agentul respectiv il ia
	else if (map[this->position_on_map.first][this->position_on_map.second] >= 6 && map[this->position_on_map.first][this->position_on_map.second] != 0)
	{
		for (int i = 0; i < Get_number_of_items(); i++)
		{
			if (items[i]->Get_position_x() == this->position_on_map.first && items[i]->Get_position_y() == this->position_on_map.second)
			{
				if (items[i]->Get_id() == 12)
				{
					Gear *object = dynamic_cast<Gear*>(items[i]);
					if (object)
					{
						if (round == obj.get_Round() || round == -2)
						{
							cout << "\n--------------------- | OBIECT |-------------------- - \n";
							cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
						}
						this->setHealth(this->getHealth() + object->Get_health());
						this->setDefence(this->getDefence() + object->Get_defence());
						this->setMovement(this->getMovement() + object->Get_movement());
						if (this->getMovement() > 3)
							this->setMovement(3);
						this->items_collected.push_back(object);
						items.erase(items.begin() + i);
						i--;
						Set_number_of_items(Get_number_of_items() - 1);
					}

				}
				else if (items[i]->Get_id() == 6 && items[i]->Get_id()==14)
				{
					Items *object = dynamic_cast<Items*>(items[i]);
					if (object)

					{
						if (round == obj.get_Round() || round == -2)
						{
							cout << "\n--------------------- | OBIECT |-------------------- - \n";
							cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
						}
						this->setDamage(this->getDamage() + object->Get_damage());
						this->items_collected.push_back(object);
						items.erase(items.begin() + i);
						i--;
						Set_number_of_items(Get_number_of_items() - 1);
					}

				}

				else if (items[i]->Get_id() == 7)
				{
					Knife *object = dynamic_cast<Knife*>(items[i]);
					if (object)

					{
						if (round == obj.get_Round() || round == -2)
						{
							cout << "\n--------------------- | OBIECT |-------------------- - \n";
							cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
						}
						this->setDamage(this->getDamage() + object->Get_damage());
						this->setSkill(this->getSkill() + object->Get_skill());
						if (this->getSkill() > 3)
							this->setSkill(3);
						this->items_collected.push_back(object);
						items.erase(items.begin() + i);
						i--;
						Set_number_of_items(Get_number_of_items() - 1);
					}

				}

				else if (items[i]->Get_id() == 8)
				{
					Pistols *object = dynamic_cast<Pistols*>(items[i]);
					if (object)

					{
						if (round == obj.get_Round() || round == -2)
						{
							cout << "\n--------------------- | OBIECT |-------------------- - \n";
							cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
						}
						this->setDamage(this->getDamage() + object->Get_damage());
						this->setSkill(this->getSkill() + object->Get_skill());
						if (this->getSkill() > 3)
							this->setSkill(3);
						this->items_collected.push_back(object);
						items.erase(items.begin() + i);
						i--;
						Set_number_of_items(Get_number_of_items() - 1);
					}

				}
				else if (items[i]->Get_id() == 9)
				{
					Heavy *object = dynamic_cast<Heavy*>(items[i]);
					if (object)

					{
						if (round == obj.get_Round() || round == -2)
						{
							cout << "\n--------------------- | OBIECT |-------------------- - \n";
							cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
						}
						this->setDamage(this->getDamage() + object->Get_damage());
						this->setSkill(this->getSkill() + object->Get_skill());
						if (this->getSkill() > 3)
							this->setSkill(3);
						this->items_collected.push_back(object);
						items.erase(items.begin() + i);
						i--;
						Set_number_of_items(Get_number_of_items() - 1);
					}

				}

				else if (items[i]->Get_id() == 10)
				{
					AK47 *object = dynamic_cast<AK47*>(items[i]);
					if (object)

					{
						if (round == obj.get_Round() || round == -2)
						{
							cout << "\n--------------------- | OBIECT |-------------------- - \n";
							cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
						}
						this->setDamage(this->getDamage() + object->Get_damage());
						this->setSkill(this->getSkill() + object->Get_skill());
						if (this->getSkill() > 3)
							this->setSkill(3);
						this->setMovement(this->getMovement() + object->Get_movement());
						if (this->getMovement() > 3)
							this->setMovement(3);
						this->items_collected.push_back(object);
						items.erase(items.begin() + i);
						i--;
						Set_number_of_items(Get_number_of_items() - 1);
					}

				}

				else if (items[i]->Get_id() == 11)
				{
				Items *object = dynamic_cast<Items*>(items[i]);
				if (object)

				{
					if (round == obj.get_Round() || round == -2)
					{
						cout << "\n--------------------- | OBIECT |-------------------- - \n";
						cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
					}
					this->setDamage(this->getDamage() + object->Get_damage());
					this->setMovement(this->getMovement() + object->Get_movement());
					if (this->getMovement() > 3)
						this->setMovement(3);
					this->items_collected.push_back(object);
					items.erase(items.begin() + i);
					i--;
					Set_number_of_items(Get_number_of_items() - 1);
				}

				}

				else if (items[i]->Get_id() == 13)
				{
				Gear *object = dynamic_cast<Gear*>(items[i]);
				if (object)

				{
					if (round == obj.get_Round() || round == -2)
					{
						cout << "\n--------------------- | OBIECT |-------------------- - \n";
						cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
					}
					this->setDefence(this->getDefence() + object->Get_defence());
					this->setMovement(this->getMovement() + object->Get_movement());
					if (this->getMovement() > 3)
						this->setMovement(3);
					this->items_collected.push_back(object);
					items.erase(items.begin() + i);
					i--;
					Set_number_of_items(Get_number_of_items() - 1);
				}

				}

				else if (items[i]->Get_id() ==15)
				{
				Grenade *object = dynamic_cast<Grenade*>(items[i]);
				if (object)

				{
					if (round == obj.get_Round() || round == -2)
					{
						cout << "\n--------------------- | OBIECT |-------------------- - \n";
						cout << "Agentul " << this->Get_Name() << " a gasit " << object->Get_name() << " ! \n";
					}
					this->setDamage(this->getDamage() + object->Get_damage());
					this->setDefence(this->getDefence() + object->Get_defence());
					this->items_collected.push_back(object);
					items.erase(items.begin() + i);
					i--;
					Set_number_of_items(Get_number_of_items() - 1);
				}

				}
			}
		}
	}
}