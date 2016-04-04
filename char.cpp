#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>

#include "char.h"


Knight::Knight(Map &m)
{
	int x = rand() % m.Width();
	int y = rand() % m.Height();
	while (m.Map_elem(x, y) != '.')
	{
		x = rand() % m.Width();
		y = rand() % m.Height();
	}
	posX = x;
	posY = y;
	health = 100;
	damage = 10;
	win = 0;
	level = 0;
	mob_to_next_level = 3;
	m.Create_Char(x, y, 'K');
}

int Knight::Winner()
{
	return win;
}

Princess::Princess(Map &m)
{
	Find_x_y(m);
	health = 100;
	damage = 0;
	m.Create_Char(posX, posY, 'P');
}

Zombie::Zombie(int x, int y, Map &m)
{
	health = 20;
	damage = 10;
	posX = x;
	posY = y;
	m.Create_Char(x, y, 'Z');
}

void Character::Find_x_y(Map &m)
{
	int x = rand() % m.Width();
	int y = rand() % m.Height();
	while (m.Map_elem(x, y) != '.')
	{
		x = rand() % m.Width();
		y = rand() % m.Height();
	}
	posX = x;
	posY = y;
}

Zombie::Zombie(Map &m)
{
	Find_x_y(m);
	health = 20;
	damage = 10;
	m.Create_Char(posX, posY, 'Z');
}

void Zombie::asPlace(int x, int y, Map &m)
{
	posX = x;
	posY = y;
	m.Create_Char(x, y, 'Z');
}

Dragon::Dragon(int x, int y, Map &m)
{
	health = 100;
	damage = 25;
	posX = x;
	posY = y;
	m.Create_Char(x, y, 'D');
}

Dragon::Dragon(Map &m)
{
	Find_x_y(m);
	health = 100;
	damage = 25;
	m.Create_Char(posX, posY, 'D');
}

void Dragon::asPlace(int x, int y, Map &m)
{
	posX = x;
	posY = y;
	m.Create_Char(x, y, 'D');
}

int Character::HitPoints()
{
	return health;
}

int Character::cntDamage()
{
	return damage;
}

void Knight::LevelUp()
{
	level++;
	health = 100 + 10*level;
	damage += 2;
	mob_to_next_level = 3 + level;
}

void Knight::Move(Map &m, std::vector<Character*> &All)
{
	int i, tx, ty, changed = 0;
	char c;
	int good_char = 1;
	
	while (good_char)
	{
		std::cin >> c;
		if (c == 'w') {tx = posX; ty = posY - 1; good_char = 0;}
		if (c == 's') {tx = posX; ty = posY + 1; good_char = 0;}
		if (c == 'a') {tx = posX - 1; ty = posY; good_char = 0;}
		if (c == 'd') {tx = posX + 1; ty = posY; good_char = 0;}
	}
	c = m.Map_elem(tx, ty);
	
	if (c == '.')
	{
		m.Change(tx, ty, posX, posY);
		changed = 1;
	}
	else if (c == 'P')
	{
		m.Change(tx, ty, posX, posY);
		changed = 1;
		win = 1;		
		return;
	}
	else if (c != '#')
	{
		for (i = 2; i < All.size(); i++)
		{
			if ((All[i]->PosX() == tx) && (All[i]->PosY() == ty))
				if (All[i]->Damage(cntDamage()))
				{
					All.erase(All.begin() + i);
					m.Change(tx, ty, posX, posY);
					mob_to_next_level--;
					if (!mob_to_next_level)
						LevelUp();
					changed = 1;
					break;
				}						
		}
	 
	}
	if (changed){posX = tx; posY = ty;}
}

void Princess::Move(Map &m, std::vector<Character*> &All)
{
	
}

void Monster::Move(Map &m, std::vector<Character*> &All)
{
	int changed = 0;
	int tx, ty, i;
	int c = rand() % 4;
	if (c == 0){tx = posX + 1;ty = posY;}
	if (c == 1){tx = posX - 1;ty = posY;}		
	if (c == 2){tx = posX;ty = posY + 1;}
	if (c == 3){tx = posX; ty = posY - 1;}
	
	c = m.Map_elem(tx, ty);
	
	if (c == '.')
	{
		m.Change(tx, ty, posX, posY);
		changed = 1;
	}
	else if ((c == 'K') || (c == 'P'))
	{
		for (i = 0; i < 2; i++)
		{
			if ((All[i]->PosX() == tx) && (All[i]->PosY() == ty))
			{
				if (All[i]->Damage(cntDamage()))
				{
					All.erase(All.begin() + i);
					m.Change(tx, ty, posX, posY);
					changed = 1;
					break;
				}
			}
		}	
	}
	if (changed){posX = tx; posY = ty;}
}

int Character::Damage(int dam)
{
	health -= dam;
	return health <= 0 ? 1 : 0;
}

int Character::PosX()
{
	return posX;
}

int Character::PosY()
{
	return posY;
}

int Character::Level()
{
	return level;
}

int Knight::CheckWin(Princess P)
{
	return ((PosX() == P.PosX()) && (PosY() == P.PosY()));
}
