#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <ncurses.h>
#include <string>

#include "map.h"
#include "char.h"
#include "config.h"
#include "editor.h"

using namespace std;

int i;
int Z_num = 40;
int D_num = 10;
int S_num = 1;
Map Test_map("map");
int Cnt_move = 0;

int game_over(Character* K, Character* P)
{
	if ((K->hit_points() <= 0) || (P->hit_points() <= 0))
	{
		erase();
		printw("Game Over. ");
		if (K->hit_points() <= 0)
			printw("Knight Dead!\n");
		else
			printw("Princess Dead!\n");
		return 1;
	}
	if (K->winner())
	{
		erase();
		printw("Knight Win!\n");
		return 1;
	}
	return 0;
}

void next_move(Map& _Test_map)
{
	Cnt_move++;
	int i = 0;
	while (i < _Test_map.vec_size())
	{
		int temp = _Test_map.select_char(i)->move(_Test_map); 
		
		if (temp == -1){ _Test_map.vec_erase(i); i--; } //Если move объекта возвращает -1, то удаляем этот объект
		
		if (temp == -2){ Test_map.cnt_health_change(-1); } //Если move возвращает -2, значит объект съел жизненный бонус
		
		if (temp >= 1) //Если move объекта возвращает число >= 1, то удаляем элемент списка под этим номером и сам объект
		{
			if (_Test_map.symbol_char(temp) == Char_health)
				Test_map.cnt_health_change(-1);
			if (temp > i)
			{
				_Test_map.vec_erase(temp);
				_Test_map.vec_erase(i);
			}
			else
			{
				_Test_map.vec_erase(i);
				_Test_map.vec_erase(temp);
			}
			i--;			
		}
		i++;
	}
	
	if ((Cnt_move % 5 == 0) && (Test_map.get_cnt_health() < 5))
	{
		new HealthBonus(_Test_map);
		Test_map.cnt_health_change(1);;
	}
	if (Test_map.get_cnt_health() >= 5)
		Cnt_move = 0;
}

void diff_level()
{
	erase();
	int Difficult;
	printw("1 Easy, 2 Medium, 3 Hard, 4 HELL!!!\n");
	Difficult = getch();
	if (Difficult == '2'){Z_num *= 2; D_num *= 2; S_num *= 2;}
	if (Difficult == '3'){Z_num *= 3; D_num *= 3; S_num *= 3;}
	if (Difficult == '4'){Z_num *= 4; D_num *= 4; S_num *= 4;}
}

void edit_map()
{
	Editor E_tool;
	Test_map = E_tool.main_edit_loop();
}

void make_choice()
{
	printw("E - editor\nD - difficult\nAny button - start game\n");
	char c = 'q';
	while (c != 'z')
	{
		c = getch();
		if (c == 'e'){ edit_map(); return; }
		if (c == 'd'){ diff_level(); return;}
	}
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
	init_pair(5, COLOR_WHITE, COLOR_RED);
}

int main()
{
	srand(time(0));
	
	init_ncurses();
	
	Configuration Con("/media/data/Users/Гусаров Владислав/Desktop/4 Семестр/Технологии программирования/RogueLike/config");
	if (Con.read_file())
	{
		endwin();
		return 0;
	}

	make_choice();	

	Z_num = Test_map.clear_count() / 10;
	D_num = Z_num / 5;
	S_num = D_num / 5;
	
	erase();
	
	
	if (!Test_map.is_edit())
	{	
		new Graveyard(Test_map);
		new DragonNest(Test_map);
		new Princess(Test_map);
		new Knight(Test_map);
		for (int i = 0 ; i < Z_num; i++)
			new Zombie(Test_map);
		for (int i = 0 ; i < D_num; i++)
			new Dragon(Test_map);
		for (int i = 0 ; i < S_num; i++)
			new Sorcerer(Test_map);
	}

	erase();
	Test_map.display();

	while (!game_over(Test_map.select_char(1), Test_map.select_char(0)))
	{
		printw("Knight-Health: %d; Princess-Health: %d; Enemies: %d; Level: %d;\n", Test_map.select_char(1)->hit_points(), Test_map.select_char(0)->hit_points(), Test_map.vec_size() - 2, Test_map.select_char(1)->level());
		next_move(Test_map);
		
		for (i = 0; i < Test_map.unvec_size(); i++)
			Test_map.select_unchar(i)->move(Test_map);
		
		erase();
		Test_map.display();
		
	}
	while (getch() != 'q'){}
	endwin();
	return 0;
}
