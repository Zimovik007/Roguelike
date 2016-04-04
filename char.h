#pragma once

#include <vector>
#include "map.h"

//galeksanin@game_forest.com

class Character
{	
public:
	virtual void Move(Map &m, std::vector<Character*> All) = 0;
	virtual int Damage(int dam);
	virtual int HitPoints();
	virtual int cntDamage();
	virtual int PosX();
	virtual int PosY();
protected:
	int health;
	int damage;
	int posX;
	int posY;
};

class Princess : public Character
{
public:
	Princess(int x, int y, Map &m);
	void Move(Map &m, std::vector<Character*> All);
};

class Knight : public Character
{
public:
	Knight(int x, int y, Map &m);
	int Winner();
	void Move(Map &m, std::vector<Character*> All);
	int CheckWin(Princess P);
protected:
	int win;
};

class Monster : public Character
{
public:
	void Move(Map &m, std::vector<Character*> All);
};

class Zombie : public Monster
{
public:
	Zombie();
	Zombie(int x, int y, Map &m);
	void asPlace(int x, int y, Map &m);
};

class Dragon : public Monster
{
public:
	Dragon();
	Dragon(int x, int y, Map &m);
	void asPlace(int x, int y, Map &m);
};
