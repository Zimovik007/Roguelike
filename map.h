#pragma once

class Map
{
private:
	int height;
	int width;
	char **map;
public:
	Map();
	void display();
	void Create_Char(int x, int y, char c);
	void Change(int x1, int y1, int x2, int y2);
	char Map_elem(int x, int y);
	int Height();
	int Width();
};
