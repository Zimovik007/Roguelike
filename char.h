#pragma once

#include <vector>
#include "map.h"

//galeksanin@game_forest.com

class Character
{	
public:
	virtual int move(Map &M) = 0;
	virtual void find_x_y(Map &M);
	virtual int damage(int Dam);
	virtual int hit_points();
	virtual int cnt_damage();
	virtual int pos_x();
	virtual int pos_y();
	virtual void get_health();
	virtual char get_symbol();
protected:
	int Max_health;
	int Health;
	int Damage;
	int Pos_x;
	int Pos_y;
	char Symbol;
};

// GOOD CHARACTERS

class Princess : public Character
{
public:
	Princess(Map &M);
	int move(Map &M);
};

class Knight : public Character
{
public:
	Knight(Map &M);
	int winner();
	int move(Map &M);
	int check_win(Princess P);
	void level_up();
	int level();
protected:
	int Level;
	int Win;
	int Mob_to_next_level;
};

// MONSTERS

class Monster : public Character
{
public:
	int move(Map &M);
};

class Zombie : public Monster
{
public:
	Zombie(Map &M);
	Zombie(int X, int Y, Map &M);
};

class Dragon : public Monster
{
public:
	Dragon(Map &M);
	Dragon(int X, int Y, Map &M);
};

class Sorcerer : public Monster
{
public:
	Sorcerer(Map &M);
	int move(Map &M);
private:
	int Cnt_move;
};

// SPELLS

//FIREBALL

class Fireball : public Character
{
public:
	Fireball(int X, int Y, char C, Map &M);
	int move(Map &M);
};

// OBJECTS

// GRAVEYARD

class Graveyard : public Character
{
public:
	Graveyard(Map &M);
	int move(Map &M);
private:
	int Cnt_move;
};

// DRAGON NEST

class DragonNest : public Character
{
public:
	DragonNest(Map &M);
	int move(Map &M);
private:
	int Cnt_move;
};

// BONUS

// HEALTH

class HealthBonus : public Character
{
public:
	HealthBonus(Map &M);
	int move(Map &M);
};
