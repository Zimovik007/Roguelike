#pragma once

#include "map.h"
#include "point.h"
#include "char.h"

class Editor{
private:
	Map E_map;
	Point Arrow;
public:
	Editor();
	Editor(const char* Path);
	void save_map();
	Map load_map();
	int  play_map();
	void change_map();
	void move_arrow();
	void delete_barrier();
	void add_obj();
	Map  main_edit_loop();
	bool main_button_handle(const char c);
	void obj_button_handle(const char c);
	void obj_edit_loop();
};
