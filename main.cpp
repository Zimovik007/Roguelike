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
int S_num = 1;
Map Test_map;
int Cnt_move = 0, Cnt_health = 0;

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
	Cnt_move++;
	int i = 0;
	while (i < Test_map.vec_size())
	{
		int temp = Test_map.select_char(i)->move(Test_map); 
		
		if (temp == -1){ Test_map.vec_erase(i); i--; } //Если move объекта возвращает -1, то удаляем этот объект
		
		if (temp == -2){ Cnt_health--; } //Если move возвращает -2, значит объект съел жизненный бонус
		
		if (temp >= 1) //Если move объекта возвращает число >= 1, то удаляем элемент списка под этим номером и сам объект
		{
			if (Test_map.symbol_char(temp) == Char_health)
				Cnt_health--;
			if (temp > i)
			{
				Test_map.vec_erase(temp);
				Test_map.vec_erase(i);
			}
			else
			{
				Test_map.vec_erase(i);
				Test_map.vec_erase(temp);
			}
			i--;			
		}
		i++;
	}
	
	if ((Cnt_move % 5 == 0) && (Cnt_health < 5))
	{
		new HealthBonus(Test_map);
		Cnt_health++;
	}
	if (Cnt_health == 5)
		Cnt_move = 0;
}

void diff_level()
{
	int Difficult;
	printw("1 Easy, 2 Medium, 3 Hard, 4 HELL!!!\n");
	Difficult = getch();
	if (Difficult == '2'){Z_num *= 2; D_num *= 2; S_num *= 2;}
	if (Difficult == '3'){Z_num *= 3; D_num *= 3; S_num *= 3;}
	if (Difficult == '4'){Z_num *= 4; D_num *= 4; S_num *= 4;}
}

void init_ncurses()
{
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	noecho();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
}

int main()
{
	srand(time(0));
	
	init_ncurses();
	diff_level();	
	
	
	Graveyard Yard(Test_map);
	DragonNest Nest(Test_map);
	
	Princess P(Test_map);
	Knight K(Test_map);
	
	for (int i = 0 ; i < Z_num; i++)
		new Zombie(Test_map);
	for (int i = 0 ; i < D_num; i++)
		new Dragon(Test_map);
	for (int i = 0 ; i < S_num; i++)
		new Sorcerer(Test_map);
	
	erase();
	Test_map.display();
	while (!game_over(K, P))
	{
		printw("Knight-Health: %d; Princess-Health: %d; Enemies: %d; Level: %d;\n", K.hit_points(), P.hit_points(), Test_map.vec_size() - 2, K.level());
		next_move();
		
		Nest.move(Test_map);
		Yard.move(Test_map);
		
		erase();
		Test_map.display();
		
	}
	while (getch() != 'q'){}
	endwin();
	return 0;
}
