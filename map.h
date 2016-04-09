#pragma once

class Map
{
private:
	int Height;
	int Width;
	char **Map_data;
public:
	Map();
	void display();
	void create_char(int X, int Y, char c);
	void change(int X1, int Y1, int X2, int Y2);
	char map_elem(int X, int Y);
	int height();
	int width();
};
