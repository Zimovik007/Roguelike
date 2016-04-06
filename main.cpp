#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <ncurses.h>

#include "map.h"
#include "char.h"

int i;
int Z_num = 40;
int D_num = 10;
Map test_map;
std::vector<Character*> All_Char;

int GameOver(Knight K, Princess P)
{
	if (K.Winner())
	{
		erase();
		printw("Knight Win!\n");
		return 1;
	}
	if ((K.HitPoints() <= 0) || (P.HitPoints() <= 0))
	{
		erase();
		printw("Game Over. ");
		if (K.HitPoints() <= 0)
			printw("Knight Dead!\n");
		else
			printw("Princess Dead!\n");
		return 1;
	}
	return 0;
}

void NextMove()
{
	for (int i = 0; i < All_Char.size(); i++)
		All_Char[i]->Move(test_map, All_Char);
}

void diff_level()
{
	int difficult;
	printw("1 Easy, 2 Medium, 3 Hard, 4 HELL!!!\n");
	difficult = getch();
	if (difficult == '2'){Z_num *= 2; D_num *= 2;}
	if (difficult == '3'){Z_num *= 3; D_num *= 3;}
	if (difficult == '4'){Z_num *= 4; D_num *= 4;}
}

void init_ncurses()
{
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	noecho();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
}

int main()
{
	srand(time(0));
	
	init_ncurses();
	diff_level();	
	
	Knight K(test_map);
	Princess P(test_map);
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
	while (!GameOver(K, P))
	{
		printw("Knight-Health: %d; Princess-Health: %d; Enemies: %d; Level: %d;\n", K.HitPoints(), P.HitPoints(), All_Char.size() - 2, All_Char[0]->Level());
		NextMove();
		erase();
		test_map.display();		
	}
	while (1){char c; c = getch(); if (c == 'q') break;}
	endwin();
	return 0;
}
