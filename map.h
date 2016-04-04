#pragma once

class Map
{
private:
	int height;
	int width;
	char map[29][127];
public:
	Map(int w1, int h1);
	void display();
	void Create_Char(int x, int y, char c);
	void Change(int x1, int y1, int x2, int y2);
	int Blocked(int x, int y);
	char Map_elem(int x, int y);
};
