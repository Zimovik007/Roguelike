#pragma once

#include <vector>
#include "map.h"

//galeksanin@game_forest.com

class Character
{	
public:
	virtual void move(Map &M) = 0;
	virtual void find_x_y(Map &M);
	virtual int damage(int Dam);
	virtual int hit_points();
	virtual int cnt_damage();
	virtual int pos_x();
	virtual int pos_y();
protected:
	int Health;
	int Damage;
	int Pos_x;
	int Pos_y;
};

class Princess : public Character
{
public:
	Princess(Map &M);
	void move(Map &M);
};

class Knight : public Character
{
public:
	Knight(Map &M);
	int winner();
	void move(Map &M);
	int check_win(Princess P);
	void level_up();
	int level();
protected:
	int Level;
	int Win;
	int Mob_to_next_level;
};

class Monster : public Character
{
public:
	void move(Map &M);
};

class Zombie : public Monster
{
public:
	Zombie(Map &M);
	Zombie(int X, int Y, Map &M);
	void as_place(int X, int Y, Map &M);
};

class Dragon : public Monster
{
public:
	Dragon(Map &M);
	Dragon(int X, int Y, Map &M);
	void as_place(int X, int Y, Map &M);
};
