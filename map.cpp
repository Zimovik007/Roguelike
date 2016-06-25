#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <ncurses.h>

#include "map.h"
#include "char.h"
#include "point.h"

using namespace std;

Map::Map(const char* path)
{
	Edit = false;
	Cnt_health = 0;
	int Size = 0;
	char c;
	FILE* Fin;
	Width = 0;
	//Задача узнать количество строк и столцов
	Fin = fopen(path, "r");
	fscanf(Fin, "%c", &c);
	while ((c != '\n') && (c != feof(Fin)))
	{
		Width++;
		fscanf(Fin, "%c", &c);		
	}
	Size = Width;
	while (!feof(Fin))
	{
		if (c != '\n')
			Size++;
		fscanf(Fin, "%c", &c);
	}
	Height = Size / Width;
	fclose(Fin);
	
	Map_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Map_data[i] = new char[Width];
	
	//
	Fin = fopen(path, "r");
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			fscanf(Fin, "%c", &Map_data[i][j]);
		}
		fscanf(Fin, "%c", &c);
	}	
}

Map::Map(const Map& Right)
{
	this->Edit = Right.Edit;
	this->Cnt_health = Right.Cnt_health;
	this->Height = Right.Height;
		this->Width = Right.Width;
		Map_data = new char*[Right.Height];
		for (int i = 0; i < Height; i++)
		{
			Map_data[i] = new char[Right.Width];
			for (int j = 0; j < Width; j++)
			{
				this->Map_data[i][j] = Right.Map_data[i][j];	
			}
		}	
	this->Unbreakable_chars = Right.Unbreakable_chars;
	this->Chars = Right.Chars;
}

void Map::gen_chars()
{
	bool _K = false, _P = false;
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			if (Map_data[i][j] == 'P')
			{
				_P = true;
				Point Temp(j, i);
				new Princess(Temp, *this);
			}
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			if (Map_data[i][j] == 'K')
			{
				_K = true;
				Point Temp(j, i);
				new Knight(Temp, *this);
			}
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
		{
			if (Map_data[i][j] == 'Z')
			{ 
				Point Temp(j, i);
				new Zombie(Temp, *this);
			}
			else
			if (Map_data[i][j] == 'D')
			{ 
				Point Temp(j, i);
				new Dragon(Temp, *this);
			}
			else
			if (Map_data[i][j] == 'S')
			{ 
				Point Temp(j, i);
				new Sorcerer(Temp, *this);
			}
			else
			if (Map_data[i][j] == '@')
			{ 
				Point Temp(j, i);
				new DragonNest(Temp, *this);
			}
			else
			if (Map_data[i][j] == '%')
			{ 
				Point Temp(j, i);
				new Graveyard(Temp, *this);
			}
			else
			if (Map_data[i][j] == '+')
			{ 
				Point Temp(j, i);
				new HealthBonus(Temp, *this);
			}
		}
	if (!_K || !_P)
	{
		endwin();
		cout << "Map is no good" << endl;
		exit(0);
	}
}

void Map::mark_as_edited()
{
	Edit = true;
}

bool Map::is_edit()
{
	return Edit;
}

void Map::cnt_health_change(int i)
{
	Cnt_health += i;
}

int Map::get_cnt_health()
{
	return Cnt_health;
}

void Map::display()
{
	for (int i = 0; i < Height; i++, printw("\n"))
		for (int j = 0; j < Width; j++)
		{
			if (Map_data[i][j] == Char_knight) //Цвет рыцаря
			{
				attron(COLOR_PAIR(1)); 
				addch(Map_data[i][j]); 
				attroff(COLOR_PAIR(1));
			}
			else 
			if (Map_data[i][j] == Char_princess) //Цвет принцессы
			{
				attron(COLOR_PAIR(2)); 
				addch(Map_data[i][j]); 
				attroff(COLOR_PAIR(2));
			}
			else
			if (Map_data[i][j] == Char_wall) //Цвет стен
			{
				attron(A_BOLD); 
				addch(Map_data[i][j]); 
				attroff(A_BOLD);
			}
			else
			if ((Map_data[i][j] == Char_nest)       || 
			    (Map_data[i][j] == Char_graveyard))   //Цвет кладбища и гнезда
			{
				attron(COLOR_PAIR(4)); 
				addch(Map_data[i][j]); 
				attroff(COLOR_PAIR(4));
			}
			else
			if ((Map_data[i][j] == Char_fireball_up)    || 
			    (Map_data[i][j] == Char_fireball_down)  || 
			    (Map_data[i][j] == Char_fireball_left)  || 
			    (Map_data[i][j] == Char_fireball_right))  //Цвет огненных шаров
			{
				attron(COLOR_PAIR(3)); 
				addch(Map_data[i][j]); 
				attroff(COLOR_PAIR(3));
			}
			else
			if (Map_data[i][j] == Char_health)  //цвет бонуса здоровья
			{
				attron(COLOR_PAIR(4)); 
				attron(A_BOLD); 
				addch(Map_data[i][j]);  
				attroff(A_BOLD);
				attroff(COLOR_PAIR(4));
			}
			else
				addch(Map_data[i][j]);
		}	
}

int Map::clear_count()
{
	int cnt = 0;
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			if (Map_data[i][j] == Char_empty)
				cnt++;
	return cnt;
}

void Map::change_up()
{
	char** Temp_data;
	Temp_data = new char*[Height-1];
	for (int i = 0; i < Height - 1; i++)
		Temp_data[i] = new char[Width];
	for (int i = 0; i < Height - 1; i++)
		for (int j = 0; j < Width; j++)
			Temp_data[i][j] = Map_data[i][j];
	Height--;
	Map_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Map_data[i] = new char[Width];
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			Map_data[i][j] = Temp_data[i][j];
	for (int i = 0; i < Width; i++)
		Map_data[Height-1][i] = '#';
	return;
}

void Map::change_left()
{
	char** Temp_data;
	Temp_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Temp_data[i] = new char[Width-1];
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width-1; j++)
			Temp_data[i][j] = Map_data[i][j];
	Width--;
	Map_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Map_data[i] = new char[Width];
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			Map_data[i][j] = Temp_data[i][j];
	for (int i = 0; i < Height; i++)
		Map_data[i][Width-1] = '#';
	return;
}

void Map::change_right()
{
	char** Temp_data;
	Temp_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Temp_data[i] = new char[Width+1];
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width-1; j++)
			Temp_data[i][j] = Map_data[i][j];
	Width++;
	Map_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Map_data[i] = new char[Width];
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			Map_data[i][j] = Temp_data[i][j];
	for (int i = 0; i < Height; i++)
	{
		if ((i > 0) && (i < Height - 1))
			Map_data[i][Width-2] = '.';
		else
			Map_data[i][Width-2] = '#';
		Map_data[i][Width-1] = '#';
	}
	return;
}

void Map::change_down()
{
	char** Temp_data;
	Temp_data = new char*[Height+1];
	for (int i = 0; i < Height+1; i++)
		Temp_data[i] = new char[Width];
	for (int i = 0; i < Height-1; i++)
		for (int j = 0; j < Width; j++)
			Temp_data[i][j] = Map_data[i][j];
	Height++;
	Map_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Map_data[i] = new char[Width];
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			Map_data[i][j] = Temp_data[i][j];
	for (int i = 0; i < Width; i++)
	{
		if ((i > 0) && (i < Width - 1))
			Map_data[Height-2][i] = '.';
		else
			Map_data[Height-2][i] = '#';
		Map_data[Height-1][i] = '#';
	}
	return;
}

void Map::paint_cell(Point P)
{
	move(P.get_y() + 7, P.get_x());
	attron(COLOR_PAIR(5)); 
	addch(Map_data[P.get_y()][P.get_x()]); 
	attroff(COLOR_PAIR(3));
	move(P.get_y() + 7 + Height - 1, 0);
}

int Map::vec_size()
{
	return Chars.size();
}

int Map::unvec_size()
{
	return Unbreakable_chars.size();
}

void Map::vec_erase(int i)
{
	Chars.erase(Chars.begin() + i);
}

void Map::vec_erase(Point& P)
{
	for (int i = 0; i < Chars.size(); i++)
	{
		if ((Chars[i]->pos_x() == P.get_x()) && (Chars[i]->pos_y() == P.get_y()))
		{
			Chars.erase(Chars.begin() + i);
			break;
		}
	}
}

void Map::unvec_erase(int i)
{
	Unbreakable_chars.erase(Unbreakable_chars.begin() + i);
}

void Map::unvec_erase(Point& P)
{
	for (int i = 0; i < Unbreakable_chars.size(); i++)
	{
		if ((Unbreakable_chars[i]->pos_x() == P.get_x()) && (Unbreakable_chars[i]->pos_y() == P.get_y()))
		{
			Unbreakable_chars.erase(Unbreakable_chars.begin() + i);
			break;
		}
	}
}

void Map::create_char(Point& Pos, char c)
{
	Map_data[Pos.get_y()][Pos.get_x()] = c;
}

Character* Map::select_char(int i)
{
	return Chars.at(i);
}

Character* Map::select_unchar(int i)
{
	return Unbreakable_chars.at(i);
}

void Map::change(Point& P1, Point& P2)
{
	Map_data[P1.get_y()][P1.get_x()] = Map_data[P2.get_y()][P2.get_x()];
	Map_data[P2.get_y()][P2.get_x()] = Char_empty;
}

char Map::map_elem(Point& P)
{
	return Map_data[P.get_y()][P.get_x()];
}

char Map::map_elem(int X, int Y)
{
	return Map_data[Y][X];
}

void Map::add_to_vector(Character* address)
{
	Chars.push_back(address);
}

void Map::add_to_unvector(Character* address)
{
	Unbreakable_chars.push_back(address);
}

void Map::push_char_front(Character* C)
{
	Chars.insert(Chars.begin(), C);
}

int Map::height()
{
	return Height;
}

int Map::width()
{
	return Width;
}

int Map::symbol_char(int i)
{
	return Chars.at(i)->get_symbol();
}
