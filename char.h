#pragma once

#include <vector>
#include "map.h"
#include "point.h"

#define Char_knight         'K'
#define Char_princess       'P'
#define Char_zombie         'Z'
#define Char_dragon         'D'
#define Char_sorcerer       'S'
#define Char_empty          '.'
#define Char_wall           '#'
#define Char_health         '+'
#define Char_graveyard      '%'
#define Char_nest           '@'
#define Char_fireball_up    '^'
#define Char_fireball_down  'v'
#define Char_fireball_right '>'
#define Char_fireball_left  '<'

extern int 
	Hp_knight,
	Hp_zombie,
	Hp_dragon,
	Hp_sorcerer,
	Hp_princess,
	Hp_fireball,
	Dm_knight,
	Dm_zombie,
	Dm_dragon,
	Dm_sorcerer,
	Dm_princess,
	Dm_fireball;

//galeksanin@game_forest.com

class Character
{	
public:
	virtual int   move(Map &M) = 0;
	virtual int   winner();
	virtual void  find_x_y(Map &M);
	virtual int   damage(int Dam);
	virtual int   hit_points();
	virtual int   cnt_damage();
	virtual int   pos_x();
	virtual int   pos_y();
	virtual void  change_pos(Point Temp, char c, Map& M);
	virtual Point pos();
	virtual void  get_health();
	virtual char  get_symbol();
	virtual int   level();
protected:
	int Max_health;
	int Health;
	int Damage;
	Point Pos;
	char Symbol;
};

// GOOD CHARACTERS

class Princess : public Character
{
public:
	Princess(Map &M);
	Princess(Point Temp, Map &M);
	int move(Map &M);
};

class Knight : public Character
{
public:
	Knight(Map &M);
	Knight(Point Temp, Map &M);
	int winner() override;
	int move(Map &M);
	int check_win(Princess P);
	void level_up();
	virtual int level();
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
	Zombie(Point Temp, Map &M);
};

class Dragon : public Monster
{
public:
	Dragon(Map &M);
	Dragon(Point Temp, Map &M);
};

class Sorcerer : public Monster
{
public:
	Sorcerer(Map &M);
	Sorcerer(Point Temp, Map &M);
	int move(Map &M);
private:
	int Cnt_move;
};

// SPELLS

//FIREBALL

class Fireball : public Character
{
public:
	Fireball(Point Temp, char C, Map &M);
	int move(Map &M);
};

// OBJECTS

// GRAVEYARD

class Graveyard : public Character
{
public:
	Graveyard(Map &M);
	Graveyard(Point Temp, Map &M);
	int move(Map &M);
private:
	int Cnt_move;
};

// DRAGON NEST

class DragonNest : public Character
{
public:
	DragonNest(Map &M);
	DragonNest(Point Temp, Map &M);
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
	HealthBonus(Point Temp, Map &M);
	int move(Map &M);
};
