#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <ncurses.h>
#include <fstream>

#include "editor.h"

using namespace std;

Editor::Editor()
{
	E_map = Map("edit_map");
	Arrow = Point(1, 1);
}

Editor::Editor(const char* Path)
{
	E_map = Map(Path);
	Arrow = Point(1, 1);
}

void Editor::obj_edit_loop()
{
	char c;
	while (c != 'q')
	{
		erase();
		printw("Move cursor:\nW - change up\nS - change down\nA - change left\nD - change right\n\n# - put #\n");
		E_map.display();
		E_map.paint_cell(Arrow);
		c = getch();
		obj_button_handle(c);
	}
}

void Editor::obj_button_handle(const char c)
{
		if ((c == 'w') && (Arrow.get_y() > 1))                  { Arrow = Arrow.move_up();    }
	else
		if ((c == 's') && (Arrow.get_y() < E_map.height() - 2)) { Arrow = Arrow.move_down();  }
	else
		if ((c == 'a') && (Arrow.get_x() > 1))                  { Arrow = Arrow.move_left();  }
	else
		if ((c == 'd') && (Arrow.get_x() < E_map.width() - 2))  { Arrow = Arrow.move_right(); }
	else
		if (c == '3') 
		{ 
			if (E_map.map_elem(Arrow) == '.')
				E_map.create_char(Arrow, '#');
		}
	else
		if (c == '.') { delete_barrier(); E_map.create_char(Arrow, '.'); }
	else
		if (c == 'k') 
		{
			if (E_map.map_elem(Arrow) == '.')
			{
				Point Temp  = E_map.select_char(1)->pos();
				E_map.create_char(Temp, '.');
				E_map.select_char(1)->change_pos(Arrow, 'K', E_map);
			}
		}
	else
		if (c == 'p') 
		{  
			if (E_map.map_elem(Arrow) == '.')
			{
				Point Temp = E_map.select_char(0)->pos();
				E_map.create_char(Temp, '.');
				E_map.select_char(0)->change_pos(Arrow, 'P', E_map);
			}
		}
	else
		if (c == '=') 
		{ 
			if (E_map.map_elem(Arrow) == '.')
			{	
				new HealthBonus(Arrow, E_map); 
				E_map.cnt_health_change(1);
			}
		}
	else
		if (c == '2') 
		{ 
			if (E_map.map_elem(Arrow) == '.')
				new DragonNest(Arrow, E_map); 
		}
	else
		if (c == '5') 
		{ 
			if (E_map.map_elem(Arrow) == '.')
				new Graveyard(Arrow, E_map); 
		}
	else
		if (c == 'D') 
		{ 
			if (E_map.map_elem(Arrow) == '.')
				new Dragon(Arrow, E_map); 
		}
	else
		if (c == 'z') 
		{ 
			if (E_map.map_elem(Arrow) == '.')
				new Zombie(Arrow, E_map); 
		}
	else
		if (c == 'S') 
		{ 
			if (E_map.map_elem(Arrow) == '.')
				new Sorcerer(Arrow, E_map); 
		}
}

bool Editor::main_button_handle(const char c)
{
		if (c == 'w') E_map.change_up();
	else
		if (c == 's') E_map.change_down();
	else
		if (c == 'a') E_map.change_left();
	else
		if (c == 'd') E_map.change_right();
	else
		if (c == 'r') { obj_edit_loop(); }
	else
		if (c == 'S') save_map();
	else
		if (c == 'l') E_map = load_map();
	else
		if (c == 'p') return true;
	return false;
}

Map Editor::main_edit_loop()
{
	char c;
	new Princess(E_map);
	new Knight(E_map);
	while (c != 'q')
	{
		erase();
		obj_button_handle(c);
		printw("Edit map:\nW - change up\nS - change down\nA - change left\nD - change right\nL - Load Map\nR - Editor objects  |  P - play map\n");
		E_map.display();
		c = getch();
		if (main_button_handle(c))
		{		
			E_map.mark_as_edited();
			return E_map;
		}
	}
	return Map("map");
}

void Editor::save_map()
{
	char str[100];
	erase();
	printw("Enter File Name:\n");
	echo();
	scanw("%s", str);
	noecho();
	ofstream fout(str);
	for (int i = 0; i < E_map.height(); i++)
	{
		for (int j = 0; j < E_map.width(); j++)
			fout << E_map.map_elem(j, i);
		fout << endl;
	}
	fout.close();
}	

Map Editor::load_map()
{
	erase();
	char str[100];
	echo();
	printw("Please, enter file name for load:\n");
	scanw("%s", str);
	Map res(str);
	res.gen_chars();
	return res;
}

void Editor::delete_barrier()
{
	if ((E_map.map_elem(Arrow) != '.') && (E_map.map_elem(Arrow) != '#'))
	{
		for (int i = 0; i < E_map.vec_size(); i++)
		{
			if (E_map.select_char(i)->pos() == Arrow)
			{
				E_map.vec_erase(i);
				break;
			}
		}
	for (int i = 0; i < E_map.unvec_size(); i++)
		{
			if (E_map.select_unchar(i)->pos() == Arrow)
			{
				E_map.unvec_erase(i);
				break;
			}
		}
	}
}