#include "Items.h"
#include "Game_Mode.h"

#include <iostream>
#include <vector>
#include <ctime>


int Items::Get_health()
{
	return 0;
}

int Items::Get_damage()
{
	return 0;
}

int Items::Get_defence()
{
	return 0;
}

int Items::Get_movement()
{
	return 0;
}

int Items::Get_skill()
{
	return 0;
}

Knife::Knife()
{
	id = 6;
	position_x = 0;
	position_y = 0;
	name = "Knife";
	damage = 2;

}
Pocket_Knife::Pocket_Knife()
{
	id = 7;
	position_x = 0;
	position_y = 0;
	name = "Pocket Knife";
	damage = 3;
	skill = 2;

}
Silencer::Silencer()
{
	id = 8;
	position_x = 0;
	position_y = 0;
	name = "Silencer";
	damage = 5;
	skill = 2;

}
AK47::AK47()
{
	id = 9;
	position_x = 0;
	position_y = 0;
	name = "AK47";
	damage = 7;
	skill = 2;
}
AWP::AWP()
{
	id = 10;
	position_x = 0;
	position_y = 0;
	name = "AWP";
	damage = 8;
	skill = 2;
	movement = 2;
}
Nova_Shotgun::Nova_Shotgun()
{
	id = 11;
	position_x = 0;
	position_y = 0;
	name = "Nova Shotgun";
	damage = 6;
	movement = 2;
}
Medic_Kit::Medic_Kit()
{
	id = 12;
	position_x = 0;
	position_y = 0;
	name = "Medic Kit";
	defence = 10;
	health = 50;
	movement = 2;
}
Kevlar_Vest::Kevlar_Vest()
{
	id = 13;
	position_x = 0;
	position_y = 0;
	name = "Kevlar Vest";
	defence = 15;
	movement = 2;
}
Grenade::Grenade()
{
	id = 14;
	position_x = 0;
	position_y = 0;
	name = "Grenade";
	damage = 9;
}
Grenade_Molotov::Grenade_Molotov()
{
	id = 15;
	position_x = 0;
	position_y = 0;
	name = "Molotov";
	damage = 8;
	defence = -1;
}

int Items::number_of_items = 0;
int Items::copy_number_of_items = 0;

void Set_position(Game_Mode &obj, Items* &items)	// Alegem random pozitia unui item
{
	srand((int)time(0));
	int **map = obj.Get_the_map();
	int x, y;
	do
	{
		x = rand() % obj.get_Length();
		y = rand() % obj.get_Width();
		items->Set_position_x(x);
		items->Set_position_y(y);

	} while (map[items->Get_position_x()][items->Get_position_y()] != 0);
}

void Items::Position_on_map(Game_Mode & obj)		// Asezam itemul pe pozitia aleasa
{
	int **map = obj.Get_the_map();
	map[this->position_x][this->position_y] = this->id;
}

void Items::Set_position_x(int x)
{
	this->position_x = x;
}
int Items::Get_position_x()
{
	return this->position_x;
}

void Items::Set_position_y(int y)
{
	this->position_y = y;
}
int Items::Get_position_y()
{
	return this->position_y;
}

int Items::Get_id()
{
	return this->id;
}
std::string Items::Get_name()
{
	return this->name;
}


