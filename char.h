#pragma once

#include <vector>
#include "map.h"

//galeksanin@game_forest.com

class Character
{	
public:
	virtual void Move(Map &m, std::vector<Character*> &All) = 0;
	virtual int Damage(int dam);
	virtual int HitPoints();
	virtual int cntDamage();
	virtual int PosX();
	virtual int PosY();
	virtual int Level();
	virtual void Find_x_y(Map &m);
protected:
	int health;
	int damage;
	int posX;
	int posY;
	int level;
};

class Princess : public Character
{
public:
	Princess(Map &m);
	void Move(Map &m, std::vector<Character*> &All);
};

class Knight : public Character
{
public:
	Knight(Map &m);
	int Winner();
	void Move(Map &m, std::vector<Character*> &All);
	int CheckWin(Princess P);
	void LevelUp();
protected:
	int win;
	int mob_to_next_level;
};

class Monster : public Character
{
public:
	void Move(Map &m, std::vector<Character*> &All);
};

class Zombie : public Monster
{
public:
	Zombie(Map &m);
	Zombie(int x, int y, Map &m);
	void asPlace(int x, int y, Map &m);
};

class Dragon : public Monster
{
public:
	Dragon(Map &m);
	Dragon(int x, int y, Map &m);
	void asPlace(int x, int y, Map &m);
};
