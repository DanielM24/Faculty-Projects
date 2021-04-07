#pragma once
#include <iostream>
#include <vector>

class Game_Mode;

class Items
{
protected:
	std::string name;			// Fiecare item in parte este carecterizat printr-un: - Nume
	int id;						//													  - Id
	int position_x;				//													  - Pozitie x pe harta
	int position_y;				//													  - Pozitie y pe harta
	static int number_of_items;
	static int copy_number_of_items;
public:
	Items() : position_x(0), position_y(0) {}					// Constructor cu lista de initializare
	friend void Set_position(Game_Mode &obj, Items* &items);	// Functie pentru generarea coordonatelor pentru iteme

	friend static int Get_number_of_items();					// Getter pentru numarul total de obiecte de pe harta
	friend void Set_number_of_items(int x);						// Setter pentru numarul total de obiecte de pe harta

	void Position_on_map(Game_Mode &obj);						// Asezarea obiectelor pe harta

	void Set_position_x(int x);									// Setter coordonata x a obiectului
	int Get_position_x();										// Getter coordonata x a obiectului

	void Set_position_y(int y);									// Setter coordonata y a obiectului
	int Get_position_y();										// Getter coordonata y a obiectului

	int Get_id();												// Getter obiect id
	std::string Get_name();										// Getter nume obiect

	virtual int Get_health();									// Getter viata bonus data de item
	virtual int Get_damage();									// Getter atac bonus dat de item
	virtual int Get_defence();									// Getter aparare bonus data de item
	virtual int Get_movement();									// Getter mobilitate bonus data de item
	virtual int Get_skill();									// Getter skill bonus dat de item
};
class Pistols : public Items									// Reprezinta o categorie de iteme
{
protected:
	int damage;	
public:
	int Get_damage() override { return this->damage; }
	virtual int Get_skill() override { return 0; }
	Pistols() {}
	~Pistols(){}
};
class Heavy : public Items										// Reprezinta o categorie de iteme
{
protected:
	int damage;
public:
	int Get_damage() override { return this->damage; }
	virtual int Get_movement() override { return 0; }
	virtual int Get_skill() override { return 0; }
	Heavy() {}
	~Heavy() {}
};
class Gear : public Items										// Reprezinta o categorie de iteme
{
protected:
	int defence;
public:
	int Get_defence() override { return this->defence; }
	virtual int Get_health() { return 0; }
	virtual int Get_movement() { return 0; }
	Gear() {}
	~Gear(){}
};
class Silencer : public Pistols									// Reprezinta un tip de item
{
protected:
	int skill;
public:
	int Get_skill() override { return this->skill; };
	Silencer();
	~Silencer() {}
};
class Knife : public Items										// Reprezinta un tip de item
{
protected:
	int damage;
public:
	int Get_damage() override { return this->damage; };
	virtual int Get_skill() { return 0; }
	Knife();
	~Knife() {}
};
class Pocket_Knife : public Knife								// Reprezinta un tip de item
{
protected:
	int skill;
public:
	int Get_skill() override { return this->skill; };
	Pocket_Knife();
	~Pocket_Knife() {}
};
class AK47 : public Heavy										// Reprezinta un tip de item
{
protected:
	int skill;
public:
	virtual int Get_movement() { return 0; };
	int Get_skill() override { return this->skill; };
	AK47();
	~AK47(){}
};
class AWP : public AK47											// Reprezinta un tip de item
{
protected:
	int movement;
public:
	int Get_movement() override{ return this->movement; };
	AWP();
	~AWP() {}
};
class Nova_Shotgun : public Items								// Reprezinta un tip de item
{
protected:
	int damage;
	int movement;
public:
	int Get_damage() override { return this-> damage; }
	int Get_movement()override { return this->movement; };
	Nova_Shotgun();
	~Nova_Shotgun() {}
};
class Medic_Kit : public Gear									// Reprezinta un tip de item
{
protected:
	int health;
	int movement;
public:
	int Get_health() override { return this->health; };
	int Get_movement() override { return this->movement; };
	Medic_Kit();
	~Medic_Kit() {}
};
class Kevlar_Vest : public Gear									// Reprezinta un tip de item
{
protected:
	int movement;
public:
	int Get_movement() override { return this->movement; };
	Kevlar_Vest();
	~Kevlar_Vest() {}
};
class Grenade : public Items									// Reprezinta un tip de item
{
protected:
	int damage;
public:
	int Get_damage() override { return this->damage; };
	virtual int Get_defence() { return 0; };
	Grenade();
	~Grenade(){}
};
class Grenade_Molotov : public Grenade							// Reprezinta un tip de item
{
protected:
	int defence;
public:
	int Get_defence() override { return this->defence; };
	Grenade_Molotov();
	~Grenade_Molotov(){}
};



