#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ncurses.h>

#include "char.h"
#include "map.h"

//CHARACTER

void Character::find_x_y(Map &M)
{
	int Cnt = 0;	
	for (int i = 0; i < M.height(); i++)
		for (int j = 0; j < M.width(); j++)
		{
			if (M.map_elem(j, i) == '.') Cnt++;
		}
	
	int Ran = rand() % Cnt;
	for (int i = 0; i < M.height(); i++)
		for (int j = 0; j < M.width(); j++)
		{
			if (M.map_elem(j, i) == '.') Ran--;
			if (!Ran)
			{
				Pos_x = j;
				Pos_y = i;
				return;
			}
		}
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
	return Pos_x;
}

int Character::pos_y()
{
	return Pos_y;
}

//KNIGHT

Knight::Knight(Map &M)
{
	find_x_y(M);
	Health = 100;
	Damage = 10;
	Win = 0;
	Level = 0;
	Mob_to_next_level = 3;
	M.create_char(Pos_x, Pos_y, 'K');	
	M.add_to_vector(this);
}

void Knight::level_up()
{
	Level++;
	Health = 100 + 10 * Level;
	Damage += 2;
	Mob_to_next_level = 3 + Level;
}

int Knight::move(Map &M)
{
	int i, Tx, Ty, Changed = 0;
	char c;
	int Good_char = 1;
	
	while (Good_char)
	{
		c = getch();
		if (c == 'w') {Tx = Pos_x; Ty = Pos_y - 1; Good_char = 0;}
		if (c == 's') {Tx = Pos_x; Ty = Pos_y + 1; Good_char = 0;}
		if (c == 'a') {Tx = Pos_x - 1; Ty = Pos_y; Good_char = 0;}
		if (c == 'd') {Tx = Pos_x + 1; Ty = Pos_y; Good_char = 0;}
		if (c == 't') {return 0;}
	}
	c = M.map_elem(Tx, Ty);
	
	if (c == '.')
	{
		M.change(Tx, Ty, Pos_x, Pos_y);
		Changed = 1;
	}
	else if (c == 'P')
	{
		M.change(Tx, Ty, Pos_x, Pos_y);
		Changed = 1;
		Win = 1;		
		return 0;
	}
	else if (c != '#')
	{
		for (i = 2; i < M.vec_size(); i++)
		{
			if ((M.select_char(i)->pos_x() == Tx) && (M.select_char(i)->pos_y() == Ty))
				if (M.select_char(i)->damage(cnt_damage()))
				{
					M.vec_erase(i);
					M.change(Tx, Ty, Pos_x, Pos_y);
					Mob_to_next_level--;
					if (!Mob_to_next_level)
						level_up();
					Changed = 1;
					break;
				}						
		}
	 
	}
	if (Changed){Pos_x = Tx; Pos_y = Ty;}
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
	return ((pos_x() == P.pos_x()) && (pos_y() == P.pos_y()));
}

//PRINCESS

Princess::Princess(Map &M)
{
	find_x_y(M);
	Health = 100;
	Damage = 0;
	M.create_char(Pos_x, Pos_y, 'P');	
	M.add_to_vector(this);
}

int Princess::move(Map &M)
{
	return 0;
}

// MONSTER

int Monster::move(Map &M)
{
	int Changed = 0;
	int Tx, Ty, i;
	int c = rand() % 4;
	if (c == 0){Tx = Pos_x + 1;Ty = Pos_y;}
	if (c == 1){Tx = Pos_x - 1;Ty = Pos_y;}		
	if (c == 2){Tx = Pos_x;Ty = Pos_y + 1;}
	if (c == 3){Tx = Pos_x; Ty = Pos_y - 1;}
	
	c = M.map_elem(Tx, Ty);
	
	if (c == '.')
	{
		M.change(Tx, Ty, Pos_x, Pos_y);
		Changed = 1;
	}
	else if (c == 'K')
	{
		for (i = 1; i < 2; i++)
		{
			if ((M.select_char(i)->pos_x() == Tx) && (M.select_char(i)->pos_y() == Ty))
			{
				if (M.select_char(i)->damage(cnt_damage()))
				{
					M.vec_erase(i);
					M.change(Tx, Ty, Pos_x, Pos_y);
					Changed = 1;
					break;
				}
			}
		}	
	}
	if (Changed){Pos_x = Tx; Pos_y = Ty;}
	return 0;
}

// ZOMBIE

Zombie::Zombie(int X, int Y, Map &M)
{
	Health = 20;
	Damage = 10;
	Pos_x = X;
	Pos_y = Y;
	M.create_char(X, Y, 'Z');	
	M.add_to_vector(this);
}

Zombie::Zombie(Map &M)
{
	find_x_y(M);
	Health = 20;
	Damage = 10;
	M.create_char(Pos_x, Pos_y, 'Z');
	M.add_to_vector(this);
}

// DRAGON

Dragon::Dragon(int X, int Y, Map &M)
{
	Health = 100;
	Damage = 25;
	Pos_x = X;
	Pos_y = Y;
	M.create_char(X, Y, 'D');	
	M.add_to_vector(this);
}

Dragon::Dragon(Map &M)
{
	find_x_y(M);
	Health = 100;
	Damage = 25;
	M.create_char(Pos_x, Pos_y, 'D');
	M.add_to_vector(this);
}

// SORCERER

Sorcerer::Sorcerer(Map &M)
{
	find_x_y(M);
	Health = 150;
	Damage = 15;
	Cnt_move = 0;
	M.create_char(Pos_x, Pos_y, 'S');
	M.add_to_vector(this);
}

int Sorcerer::move(Map &M)
{
	int Tx, Ty;
	Monster::move(M);
	Cnt_move++;
	if (!(Cnt_move % 3))
	{
		int c = rand() % 4;
		if (c == 0){Tx = Pos_x + 1; Ty = Pos_y; c = '>';}
		if (c == 1){Tx = Pos_x - 1; Ty = Pos_y; c = '<';}		
		if (c == 2){Tx = Pos_x; Ty = Pos_y + 1; c = 'v';}
		if (c == 3){Tx = Pos_x; Ty = Pos_y - 1; c = '^';}
		
		if (M.map_elem(Tx, Ty) == '.')
			new Fireball(Tx, Ty, c, M);
	}
	return 0; 
}

// FIREBALL

Fireball::Fireball(int X, int Y, char C, Map &M)
{
	Pos_x = X;
	Pos_y = Y;
	Damage = 200;
	Health = 1;
	M.create_char(Pos_x, Pos_y, C);
	M.add_to_vector(this);
}

int Fireball::move(Map &M)
{
	int i;
	int Tx, Ty;
	if (M.map_elem(Pos_x, Pos_y) == '^'){Tx = Pos_x; Ty = Pos_y - 1;}
	if (M.map_elem(Pos_x, Pos_y) == '>'){Tx = Pos_x + 1; Ty = Pos_y;}
	if (M.map_elem(Pos_x, Pos_y) == '<'){Tx = Pos_x - 1; Ty = Pos_y;}
	if (M.map_elem(Pos_x, Pos_y) == 'v'){Tx = Pos_x; Ty = Pos_y + 1;}
	
	char C = M.map_elem(Tx, Ty);
	
	if (C == '.')
	{
		M.change(Tx, Ty, Pos_x, Pos_y);
		Pos_x = Tx; 
		Pos_y = Ty;
		return 0;
	}
	else
	{
		for (i = 1; i < M.vec_size(); i++)
		{
			if ((M.select_char(i)->pos_x() == Tx) && (M.select_char(i)->pos_y() == Ty))
			{
				if (M.select_char(i)->damage(cnt_damage()))
				{
					M.change(Tx, Ty, Pos_x, Pos_y);	
					Pos_x = Tx; 
					Pos_y = Ty;		
				}
				M.change(Pos_x, Pos_y, Pos_x, Pos_y);
				return i;
			}
		}	
	}
	M.change(Pos_x, Pos_y, Pos_x, Pos_y);
	return -1;
}

// GRAVEYARD

Graveyard::Graveyard(Map &M)
{
	find_x_y(M);
	Health = 100;
	Damage = 15;
	Cnt_move = 0;
	M.create_char(Pos_x, Pos_y, '@');
}

int Graveyard::move(Map &M)
{
	Cnt_move++;
	if (!(Cnt_move % 7))
	{
		int Tx = 0, Ty = 0, i = 0;
		while ((M.map_elem(Tx, Ty) != '.') && (i < 10))
		{
			i++;
			int c = rand() % 4;
			if (c == 0){Tx = Pos_x + 1; Ty = Pos_y;}
			if (c == 1){Tx = Pos_x - 1; Ty = Pos_y;}		
			if (c == 2){Tx = Pos_x; Ty = Pos_y + 1;}
			if (c == 3){Tx = Pos_x; Ty = Pos_y - 1;}
		}
		if (i < 10)
			new Zombie(Tx, Ty, M);
	}
}

// DRAGON NEST

DragonNest::DragonNest(Map &M)
{
	find_x_y(M);
	Health = 100;
	Damage = 15;
	Cnt_move = 0;
	M.create_char(Pos_x, Pos_y, '%');
}

int DragonNest::move(Map &M)
{
	Cnt_move++;
	if ((Cnt_move % 15) == 0)
	{
		int Tx = 0, Ty = 0, i = 0;
		while ((M.map_elem(Tx, Ty) != '.') && (i < 10))
		{
			i++;
			int c = rand() % 4;
			if (c == 0){Tx = Pos_x + 1; Ty = Pos_y;}
			if (c == 1){Tx = Pos_x - 1; Ty = Pos_y;}		
			if (c == 2){Tx = Pos_x; Ty = Pos_y + 1;}
			if (c == 3){Tx = Pos_x; Ty = Pos_y - 1;}
		}
		new Dragon(Tx, Ty, M);
	}
}
