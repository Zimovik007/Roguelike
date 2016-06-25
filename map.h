#pragma once

#include <vector>

class Character;
class Point;

class Map
{
private:
	int Height;
	int Width;
	char **Map_data;
	std::vector<Character*> Chars;
	std::vector<Character*> Unbreakable_chars;
	int Cnt_health;
	bool Edit;
public:
	~Map(){};
	Map(){};
	Map(const Map& Right);
	Map(const char* map);
	void display();
	void gen_chars();
	int clear_count();
	void create_char(Point& Pos, char c);
	char map_elem(int X, int Y);
	char map_elem(Point& P);
	bool is_edit();
	void mark_as_edited();
	void vec_erase(int i);
	void vec_erase(Point& P);
	void unvec_erase(int i);
	void unvec_erase(Point& P);
	void change(Point& P1, Point& P2);
	void change_down();
	void change_left();
	void change_right();
	void change_up();
	int symbol_char(int i);
	void add_to_vector(Character* address);
	void add_to_unvector(Character* address);
	int  vec_size();
	int  unvec_size();
	void cnt_health_change(int i);
	int get_cnt_health();
	void push_char_front(Character* C);
	Character* select_char(int i);
	Character* select_unchar(int i);
	void paint_cell(Point P);
	int height();
	int width();

	Map& operator=(Map&& Right)
	{
		this->Edit = Right.Edit;
		this->Cnt_health = Right.Cnt_health;
		this->Height = Right.Height;
		this->Width = Right.Width;
		this->Map_data = Right.Map_data;
		Right.Map_data = nullptr;
		this->Unbreakable_chars = Right.Unbreakable_chars;
		this->Chars = Right.Chars;
		Right.Chars.clear();
		Right.Unbreakable_chars.clear();
	}

	Map& operator=(const Map& Right)
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
		return *this;
	}
};
