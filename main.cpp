#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>

#include "map.h"
#include "char.h"

int i;
int Z_num = 40;
int D_num = 10;
Map test_map;
Knight K(test_map);
Princess P(test_map);
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

int main()
{
	int difficult;
	std::cout << "1 Легкий, 2 Средний, 3 Сложный" << std::endl;
	std::cin >> difficult;
	if (difficult == 2){Z_num *= 2; D_num *= 2;}
	if (difficult == 3){Z_num *= 3; D_num *= 3;}
	
	All_Char.push_back(&K);
	All_Char.push_back(&P);	
	Zombie *Z = (Zombie*)operator new(sizeof(Zombie) * Z_num);
	for (int i = 0 ; i < Z_num; i++)
	{
		new(&Z[i])Zombie(test_map);
		All_Char.push_back(&Z[i]);
	}	
	Dragon *D = (Dragon*)operator new(sizeof(Dragon) * D_num);
	for (int i = 0 ; i < D_num; i++)
	{
		new(&D[i])Dragon(test_map);
		All_Char.push_back(&D[i]);
	}
	
	test_map.display();
	while (!GameOver())
	{
		std::cout << "Knight-Health: " << K.HitPoints() 
		          << "  |  Princess-Health: " <<P.HitPoints() 
		          << "  |  Enemies: " << All_Char.size() - 2 
		          << "  |  Level: " << All_Char[0]->Level() 
		          << std::endl;
		NextMove();
		test_map.display();		
	}
	return 0;
}
