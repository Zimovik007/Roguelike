#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ncurses.h>

#include "char.h"
#include "map.h"
#include "point.h"

int Hp_knight = 100,
	Hp_zombie = 20,
	Hp_dragon = 100,
	Hp_sorcerer = 150,
	Hp_princess = 100,
	Hp_fireball = 1,
	Dm_knight = 10,
	Dm_zombie = 10,
	Dm_dragon = 25,
	Dm_sorcerer = 15,
	Dm_princess = 10,
	Dm_fireball = 200;


//CHARACTER

int Character::winner()
{}
int Character::level()
{}

void Character::find_x_y(Map &M)
{
	int Cnt = 0;	
	for (int i = 0; i < M.height(); i++)
		for (int j = 0; j < M.width(); j++)
			if (M.map_elem(j, i) == Char_empty) 
				Cnt++;
	
	int Ran = rand() % Cnt;
	for (int i = 0; i < M.height(); i++)
		for (int j = 0; j < M.width(); j++)
		{
			if (M.map_elem(j, i) == Char_empty) 
				Ran--;
			if (!Ran)
			{
				Pos = Point(j, i);
				return;
			}
		}
}

void Character::change_pos(Point Temp, char c, Map& M)
{
	Pos = Temp;
	M.create_char(Pos, c);
}

int Character::hit_points()
{
	return Health;
}

int Character::cnt_damage()
{
	return Damage;
}

int Character::damage(int Dam)
{
	Health -= Dam;
	return Health <= 0 ? 1 : 0;
}

int Character::pos_x()
{
	return Pos.get_x();
}

int Character::pos_y()
{
	return Pos.get_y();
}

void Character::get_health()
{
	Health += 10;
	if (Health > Max_health)
		Health = Max_health;
}

char Character::get_symbol()
{
	return Symbol;
}

Point Character::pos()
{
	return Pos;
}

//KNIGHT

Knight::Knight(Map &M)
{
	find_x_y(M);
	Health = Hp_knight;
	Max_health = Health;
	Damage = Dm_knight;
	Win = 0;
	Level = 0;
	Mob_to_next_level = 3;
	M.create_char(Pos, Char_knight);	
	M.add_to_vector(this);
	Symbol = Char_knight;
}

Knight::Knight(Point Temp, Map &M)
{
	Pos = Temp;
	Health = Hp_knight;
	Max_health = Health;
	Damage = Dm_knight;
	Win = 0;
	Level = 0;
	Mob_to_next_level = 3;	
	M.add_to_vector(this);
	Symbol = Char_knight;
}

void Knight::level_up()
{
	Level++;
	Health = Max_health + 10;
	Max_health = Health;
	Damage += 2;
	Mob_to_next_level = 3 + Level;
}

int Knight::move(Map &M)
{
	int i;
	Point Temp;
	char c;
	int Good_char = 1;
	
	while (Good_char)
	{
		c = getch();
		if (c == 'w') {Temp = Pos.move_up();    Good_char = 0;}
		if (c == 's') {Temp = Pos.move_down();  Good_char = 0;}
		if (c == 'a') {Temp = Pos.move_left();  Good_char = 0;}
		if (c == 'd') {Temp = Pos.move_right(); Good_char = 0;}
		if (c == 't') {return 0;}
	}
	c = M.map_elem(Temp);
	
	if (c == Char_empty)
	{
		M.change(Temp, Pos);
		Pos = Temp;
		return 0;
	}
	
	if (c == Char_princess)
	{
		M.change(Temp, Pos);
		Pos = Temp;
		Win = 1;		
		return 0;
	}
	
	if (c != Char_wall)
	{
		for (i = 2; i < M.vec_size(); i++)
		{
			if (M.select_char(i)->pos() == Temp)
				if (M.select_char(i)->damage(cnt_damage()))
				{
					M.vec_erase(i);
					M.change(Temp, Pos);
					Mob_to_next_level--;
					if (!Mob_to_next_level)
						level_up();
					Pos = Temp;
					break;
				}						
		}
	 
	}
	
	if (c == Char_health)
	{
		get_health();
		Mob_to_next_level++;
		return -2;
	}
	
	return 0;
}

int Knight::winner()
{
	return Win;
}

int Knight::level()
{
	return Level;
}

int Knight::check_win(Princess P)
{
	return (pos() == P.pos());
}

//PRINCESS

Princess::Princess(Map &M)
{
	find_x_y(M);
	Health = Hp_princess;
	Max_health = Health;
	Damage = Dm_princess;
	M.create_char(Pos, Char_princess);	
	M.add_to_vector(this);
	Symbol = Char_princess;
}

Princess::Princess(Point Temp, Map &M)
{
	Pos = Temp;
	Health = Hp_princess;
	Max_health = Health;
	Damage = Dm_princess;	
	M.add_to_vector(this);
	Symbol = Char_princess;
}

int Princess::move(Map &M)
{
	return 0;
}

// MONSTER

int Monster::move(Map &M)
{
	int i;
	int c = rand() % 4;
	
	Point Temp = Pos.random_shift(c);	
	
	c = M.map_elem(Temp);
	
	if (c == Char_empty)
	{
		M.change(Temp, Pos);
		Pos = Temp;
		return 0;
	}
	
	if (c == Char_knight)
	{
		if (M.select_char(1)->pos() == Temp)
		{
			if (M.select_char(1)->damage(cnt_damage()))
			{
				M.vec_erase(1);
				M.change(Temp, Pos);
				Pos = Temp;
			}
		}
		return 0;
	}
	
	if (c == Char_health)
	{
		M.vec_erase(Temp);
		M.change(Temp, Pos);
		Pos = Temp;
		return -2;
	}
	
	return 0;
}

// ZOMBIE

Zombie::Zombie(Map &M)
{
	find_x_y(M);
	Health = Hp_zombie;
	Max_health = Health;
	Damage = Dm_zombie;
	M.create_char(Pos, Char_zombie);
	M.add_to_vector(this);
	Symbol = Char_zombie;
}

Zombie::Zombie(Point Temp, Map &M)
{
	Pos = Temp;
	Health = Hp_zombie;
	Max_health = Health;
	Damage = Dm_zombie;
	M.create_char(Pos, Char_zombie);
	M.add_to_vector(this);
	Symbol = Char_zombie;
}

// DRAGON

Dragon::Dragon(Map &M)
{
	find_x_y(M);
	Health = Hp_dragon;
	Max_health = Health;
	Damage = Dm_dragon;
	M.create_char(Pos, Char_dragon);
	M.add_to_vector(this);
	Symbol = Char_dragon;
}

Dragon::Dragon(Point Temp, Map &M)
{
	Pos = Temp;
	Health = Hp_dragon;
	Max_health = Health;
	Damage = Dm_dragon;
	M.create_char(Pos, Char_dragon);
	M.add_to_vector(this);
	Symbol = Char_dragon;
}

// SORCERER

Sorcerer::Sorcerer(Map &M)
{
	find_x_y(M);
	Health = Hp_sorcerer;
	Max_health = Health;
	Damage = Dm_sorcerer;
	Cnt_move = 0;
	M.create_char(Pos, Char_sorcerer);
	M.add_to_vector(this);
	Symbol = Char_sorcerer;
}

Sorcerer::Sorcerer(Point Temp, Map &M)
{
	Pos = Temp;
	Health = Hp_sorcerer;
	Max_health = Health;
	Damage = Dm_sorcerer;
	Cnt_move = 0;
	M.create_char(Pos, Char_sorcerer);
	M.add_to_vector(this);
	Symbol = Char_sorcerer;
}

int Sorcerer::move(Map &M)
{
	Point Temp;
	int res = Monster::move(M);
	Cnt_move++;
	if (!(Cnt_move % 3))
	{
		int c = rand() % 4;
		if (c == 0){Temp = Pos.move_right(); c = Char_fireball_right;}
		if (c == 1){Temp = Pos.move_left(); c = Char_fireball_left;}		
		if (c == 2){Temp = Pos.move_down(); c = Char_fireball_down;}
		if (c == 3){Temp = Pos.move_up(); c = Char_fireball_up;}
		
		if (M.map_elem(Temp) == Char_empty)
			new Fireball(Temp, c, M);
	}
	return res; 
}

// FIREBALL

Fireball::Fireball(Point Temp, char C, Map &M)
{
	Pos = Temp;
	Damage = Dm_fireball;
	Health = Hp_fireball;
	Max_health = Health;
	M.create_char(Pos, C);
	M.add_to_vector(this);
	Symbol = C;
}

int Fireball::move(Map &M)
{
	int i;
	Point Temp;
	if (M.map_elem(Pos) == Char_fireball_up)   {Temp = Pos.move_up();}
	if (M.map_elem(Pos) == Char_fireball_right){Temp = Pos.move_right();}
	if (M.map_elem(Pos) == Char_fireball_left) {Temp = Pos.move_left();}
	if (M.map_elem(Pos) == Char_fireball_down) {Temp = Pos.move_down();}
	
	char C = M.map_elem(Temp);
	
	if (C == Char_empty)
	{
		M.change(Temp, Pos);
		Pos = Temp;
		return 0;
	}
	
	for (i = 1; i < M.vec_size(); i++)
	{
		if (M.select_char(i)->pos() == Temp)
		{
			if (M.select_char(i)->damage(cnt_damage()))
			{
				M.change(Temp, Pos);	
				Pos = Temp;
				M.change(Pos, Pos);
				return i;
			}
		}
	}
	
	M.change(Pos, Pos);
	return -1;
}

// GRAVEYARD

Graveyard::Graveyard(Map &M)
{
	find_x_y(M);
	Health = 100;
	Max_health = Health;
	Damage = 15;
	Cnt_move = 0;
	M.create_char(Pos, Char_graveyard);
	M.add_to_unvector(this);
	Symbol = Char_graveyard;
}

Graveyard::Graveyard(Point Temp, Map &M)
{
	Pos = Temp;
	Health = 100;
	Max_health = Health;
	Damage = 15;
	Cnt_move = 0;
	M.create_char(Pos, Char_graveyard);
	M.add_to_unvector(this);
	Symbol = Char_graveyard;
}

int Graveyard::move(Map &M)
{
	Cnt_move++;
	if ((Cnt_move % 7) == 0)
	{
		int Cnt_free = 0;
		Point Temp;
		
		for (int i = 0; i < 4; i++)
		{
			Temp = Pos.random_shift(i);
			if (M.map_elem(Temp) == Char_empty)
				Cnt_free++;
		}
		
		if (Cnt_free)
		{	
			for (int i = 0; i < 4; i++)
			{
				Temp = Pos.random_shift(i);
				if (M.map_elem(Temp) == Char_empty)
					Cnt_free--;
				if (!Cnt_free)
				{
					new Zombie(Temp, M);
					break;
				}	
			}
		}
	}
	return 0;
}

// DRAGON NEST

DragonNest::DragonNest(Map &M)
{
	find_x_y(M);
	Health = 100;
	Max_health = Health;
	Damage = 15;
	Cnt_move = 0;
	M.create_char(Pos, Char_nest);
	M.add_to_unvector(this);
	Symbol = Char_nest;
}

DragonNest::DragonNest(Point Temp, Map &M)
{
	Pos = Temp;
	Health = 100;
	Max_health = Health;
	Damage = 15;
	Cnt_move = 0;
	M.create_char(Pos, Char_nest);
	M.add_to_unvector(this);
	Symbol = Char_nest;
}

int DragonNest::move(Map &M)
{
	Cnt_move++;
	if ((Cnt_move % 15) == 0)
	{
		int Cnt_free = 0;
		Point Temp;
		
		for (int i = 0; i < 4; i++)
		{
			Temp = Pos.random_shift(i);
			if (M.map_elem(Temp) == Char_empty)
				Cnt_free++;
		}
		
		if (Cnt_free)
		{	
			for (int i = 0; i < 4; i++)
			{
				Temp = Pos.random_shift(i);
				if (M.map_elem(Temp) == Char_empty)
					Cnt_free--;
				if (!Cnt_free)
				{
					new Dragon(Temp, M);
					break;
				}	
			}
		}
	}
	return 0;
}

// HEALTH BONUS

HealthBonus::HealthBonus(Map &M)
{
	find_x_y(M);
	Health = 1;
	Max_health = Health;
	M.create_char(Pos, Char_health);
	M.add_to_vector(this);
	Symbol = Char_health;
}

HealthBonus::HealthBonus(Point Temp, Map &M)
{
	Pos = Temp;
	Health = 1;
	Max_health = Health;
	M.create_char(Pos, Char_health);
	M.add_to_vector(this);
	Symbol = Char_health;
}

int HealthBonus::move(Map &M)
{
	return 0;
}
