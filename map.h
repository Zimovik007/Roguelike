#pragma once

#include <vector>

class Character;

class Map
{
private:
	int Height;
	int Width;
	char **Map_data;
	std::vector<Character*> Chars;
public:
	Map();
	void display();
	void create_char(int X, int Y, char c);
	void change(int X1, int Y1, int X2, int Y2);
	void create_char(Character* Char);
	void add_to_vector(Character* address);
	char map_elem(int X, int Y);
	int  vec_size();
	void vec_erase(int i);
	Character* select_char(int i);
	int height();
	int width();
};
