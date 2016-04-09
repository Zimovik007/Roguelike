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
Map Test_map;
std::vector<Character*> All_char;

int game_over(Knight K, Princess P)
{
	if (K.winner())
	{
		erase();
		printw("Knight Win!\n");
		return 1;
	}
	if ((K.hit_points() <= 0) || (P.hit_points() <= 0))
	{
		erase();
		printw("Game Over. ");
		if (K.hit_points() <= 0)
			printw("Knight Dead!\n");
		else
			printw("Princess Dead!\n");
		return 1;
	}
	return 0;
}

void next_move()
{
	for (int i = 0; i < All_char.size(); i++)
		All_char[i]->move(Test_map, All_char);
}

void diff_level()
{
	int Difficult;
	printw("1 Easy, 2 Medium, 3 Hard, 4 HELL!!!\n");
	Difficult = getch();
	if (Difficult == '2'){Z_num *= 2; D_num *= 2;}
	if (Difficult == '3'){Z_num *= 3; D_num *= 3;}
	if (Difficult == '4'){Z_num *= 4; D_num *= 4;}
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
	
	Knight K(Test_map);
	Princess P(Test_map);
	All_char.push_back(&K);
	All_char.push_back(&P);	
	Zombie *Z = (Zombie*)operator new(sizeof(Zombie) * Z_num);
	for (int i = 0 ; i < Z_num; i++)
	{
		new(&Z[i])Zombie(Test_map);
		All_char.push_back(&Z[i]);
	}	
	Dragon *D = (Dragon*)operator new(sizeof(Dragon) * D_num);
	for (int i = 0 ; i < D_num; i++)
	{
		new(&D[i])Dragon(Test_map);
		All_char.push_back(&D[i]);
	}
	
	Test_map.display();
	while (!game_over(K, P))
	{
		printw("Knight-Health: %d; Princess-Health: %d; Enemies: %d; Level: %d;\n", K.hit_points(), P.hit_points(), All_char.size() - 2, K.level());
		next_move();
		erase();
		Test_map.display();		
	}
	while (getch() != 'q'){}
	endwin();
	return 0;
}
