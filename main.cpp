#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>

#include "map.h"
#include "char.h"

#define Z_num 80
#define D_num 10

int i;
Map test_map;
Knight K(test_map);
Princess P(test_map);
Zombie Z[Z_num];
Dragon D[D_num];
std::vector<Character*> All_Char;

int GameOver()
{
	if (K.Winner())
	{
		std::cout << "Knight WIN!" << std::endl;
		return 1;
	}
	if ((K.HitPoints() <= 0) || (P.HitPoints() <= 0))
	{
		std::cout << "Game over. ";
		if (K.HitPoints() <= 0)
			std::cout << "Knight dead!" << std::endl;
		else
			std::cout << "Princess dead!" << std::endl;
		return 1;
	}
	return 0;
}

void NextMove()
{
	for (int i = 0; i < All_Char.size(); i++)
		All_Char[i]->Move(test_map, All_Char);
}

void choice_position_monsters()
{
	int x = 0;
	int y = 0;
	
	for (i = 0; i < Z_num; i++)
	{
		x = 0;
		y = 0;
		while (test_map.Map_elem(x, y) != '.')
		{
			x = rand() % test_map.Width();
			y = rand() % test_map.Height();
		}
		Z[i].asPlace(x, y, test_map);
		All_Char.push_back(&Z[i]);
	}
	
	for (i = 0; i < D_num; i++)
	{
		x = 0;
		y = 0;
		while (test_map.Map_elem(x, y) != '.')
		{
			x = rand() % test_map.Width();
			y = rand() % test_map.Height();
		}
		D[i].asPlace(x, y, test_map);
		All_Char.push_back(&D[i]);
	}
}


int main()
{
	All_Char.push_back(&K);
	All_Char.push_back(&P);
	
	choice_position_monsters();
	
	test_map.display();
	while (!GameOver())
	{
		std::cout << "Knight-Health: " << K.HitPoints() << "  |  Princess-Health: " << P.HitPoints() << "  |  Enemies: " << All_Char.size() - 2 << "  |  Level: " << All_Char[0]->Level() << std::endl;
		NextMove();
		test_map.display();		
	}
	return 0;
}
