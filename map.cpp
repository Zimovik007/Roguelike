#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>

#include "map.h"

Map::Map(int w1, int h1)
{
	char c;
	height = h1;
	width = w1;
	FILE* fin = fopen("map", "r");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			fscanf(fin, "%c", &map[i][j]);
		fscanf(fin, "%c", &c);
	}	
}

void Map::display()
{
	for (int i = 0; i < height; i++, printf("\n"))
		for (int j = 0; j < width; j++)
			std::cout << map[i][j];
}

void Map::Create_Char(int x, int y, char c)
{
	map[y][x] = c;
}

void Map::Change(int x1, int y1, int x2, int y2)
{
	map[y1][x1] = map[y2][x2];
	map[y2][x2] = '.';
}

int Map::Blocked(int x, int y)
{
	return (map[y][x] != '.');
}

char Map::Map_elem(int x, int y)
{
	return map[y][x];
}
