#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>

#include "map.h"

Map::Map()
{
	int size = 0;
	char c;
	FILE* fin;
	width = 0;
	//Задача узнать количество строк и столцов
	fin = fopen("map", "r");
	fscanf(fin, "%c", &c);
	while ((c != '\n') && (c != feof(fin)))
	{
		width++;
		fscanf(fin, "%c", &c);		
	}
	size = width;
	while (!feof(fin))
	{
		if (c != '\n')
			size++;
		fscanf(fin, "%c", &c);
	}
	height = size / width;
	fclose(fin);
	
	map = new char*[height];
	for (int i = 0; i < height; i++)
		map[i] = new char[width];
	
	//
	fin = fopen("map", "r");
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

char Map::Map_elem(int x, int y)
{
	return map[y][x];
}

int Map::Height()
{
	return height;
}

int Map::Width()
{
	return width;
}
