#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ncurses.h>

#include "char.h"
#include "map.h"

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

int Knight::winner()
{
	return Win;
}

Princess::Princess(Map &M)
{
	find_x_y(M);
	Health = 100;
	Damage = 0;
	M.create_char(Pos_x, Pos_y, 'P');	
	M.add_to_vector(this);
}

Zombie::Zombie(int X, int Y, Map &M)
{
	Health = 20;
	Damage = 10;
	Pos_x = X;
	Pos_y = Y;
	M.create_char(X, Y, 'Z');	
	M.add_to_vector(this);
}

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
			}
		}
}

Zombie::Zombie(Map &M)
{
	find_x_y(M);
	Health = 20;
	Damage = 10;
	M.create_char(Pos_x, Pos_y, 'Z');
	M.add_to_vector(this);
}

void Zombie::as_place(int X, int Y, Map &M)
{
	Pos_x = X;
	Pos_y = Y;
	M.create_char(X, Y, 'Z');
}

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

void Dragon::as_place(int X, int Y, Map &M)
{
	Pos_x = X;
	Pos_y = Y;
	M.create_char(X, Y, 'D');
}

int Character::hit_points()
{
	return Health;
}

int Character::cnt_damage()
{
	return Damage;
}

void Knight::level_up()
{
	Level++;
	Health = 100 + 10 * Level;
	Damage += 2;
	Mob_to_next_level = 3 + Level;
}

void Knight::move(Map &M)
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
		if (c == 't') {return;}
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
		return;
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
}

void Princess::move(Map &M)
{
	
}

void Monster::move(Map &M)
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
	else if ((c == 'K') || (c == 'P'))
	{
		for (i = 0; i < 2; i++)
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

int Knight::level()
{
	return Level;
}

int Knight::check_win(Princess P)
{
	return ((pos_x() == P.pos_x()) && (pos_y() == P.pos_y()));
}
