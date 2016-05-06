#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <ncurses.h>

#include "map.h"
#include "char.h"

Map::Map()
{
	int Size = 0;
	char c;
	FILE* Fin;
	Width = 0;
	//Задача узнать количество строк и столцов
	Fin = fopen("map", "r");
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
	Fin = fopen("map", "r");
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
			fscanf(Fin, "%c", &Map_data[i][j]);
		fscanf(Fin, "%c", &c);
	}	
}

void Map::display()
{
	for (int i = 0; i < Height; i++, printw("\n"))
		for (int j = 0; j < Width; j++)
		{
			if (Map_data[i][j] == 'K'){attron(COLOR_PAIR(1)); addch(Map_data[i][j]); attroff(COLOR_PAIR(1));}
			else 
			if (Map_data[i][j] == 'P'){attron(COLOR_PAIR(2)); addch(Map_data[i][j]); attroff(COLOR_PAIR(2));}
			else
			if (Map_data[i][j] == '#'){attron(A_BOLD); addch(Map_data[i][j]); attroff(A_BOLD);}
			else
			if ((Map_data[i][j] == '@') || (Map_data[i][j] == '%')){attron(COLOR_PAIR(4)); addch(Map_data[i][j]); attroff(COLOR_PAIR(4));}
			else
			if ((Map_data[i][j] == '^') || (Map_data[i][j] == 'v') || (Map_data[i][j] == '<') || (Map_data[i][j] == '>')){attron(COLOR_PAIR(3)); addch(Map_data[i][j]); attroff(COLOR_PAIR(3));}
			else
				addch(Map_data[i][j]);
		}	
}

int Map::vec_size()
{
	return Chars.size();
}

void Map::vec_erase(int i)
{
	Chars.erase(Chars.begin() + i);
}

void Map::create_char(int X, int Y, char c)
{
	Map_data[Y][X] = c;
}

Character* Map::select_char(int i)
{
	return Chars[i];
}

void Map::change(int X1, int Y1, int X2, int Y2)
{
	Map_data[Y1][X1] = Map_data[Y2][X2];
	Map_data[Y2][X2] = '.';
}

char Map::map_elem(int X, int Y)
{
	return Map_data[Y][X];
}

void Map::add_to_vector(Character* address)
{
	Chars.push_back(address);
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
