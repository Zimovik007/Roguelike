#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>

#include "config.h"
#include "char.h"

using namespace std;

Configuration::Configuration(const char S[])
{
	File.open(S);
}

Configuration::~Configuration()
{
	if (File.is_open())
		File.close();
}

int Configuration::read_params(int& Health, int& Damage)
{
	string S[2];
	for (int i = 0; i < 2; i++)
	{
		getline(File, S[0]);
		getline(File, S[1]);
		if (S[0] == Param_health)
		{
			try{ Health = stoi(S[1].c_str()); }
			catch (...)
			{
				return 1;
			}
		}
		else
		if (S[0] == Param_damage)
		{
			try{ Damage = stoi(S[1].c_str()); }
			catch (...)
			{
				return 1;
			}
		}
		else
			return 1;
	}	
	return 0;	
}

int Configuration::read_file()
{
	
	if (!File.is_open())
	{
		printw("This file doesn't exist!\nGame run with - default - parameters\n");
		getch();
		return 0;
	}
	
	int error;
	string S;
	getline(File, S);
	
	if (S != Sign)
	{
		printw("It's not a configuration file!\nGame run with - default - parameters\n");
		getch();
		return 0;
	}
	
	while(getline(File, S))
	{
		if (S == Word_knight)
			error = read_params(Hp_knight,   Dm_knight);
		if (S == Word_princess)
			error = read_params(Hp_princess, Dm_princess);
		if (S == Word_zombie)
			error = read_params(Hp_zombie,   Dm_zombie);
		if (S == Word_dragon)
			error = read_params(Hp_dragon,   Dm_dragon);
		if (S == Word_sorcerer)
			error = read_params(Hp_sorcerer, Dm_sorcerer);
		if (S == Word_fireball)
			error = read_params(Hp_fireball, Dm_fireball);
		if (error)
		{
			printw("Configuration file is not correct.\nThe game will be closed!\n");
			getch();
			return 1;
		}
	}
	
	return 0;
	
}
