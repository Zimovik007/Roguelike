#pragma once

#include <string>
#include <fstream>

#define Sign          "#Roguelike"
#define Word_knight   "Knight:"
#define Word_zombie   "Zombie:"
#define Word_dragon   "Dragon:"
#define Word_sorcerer "Sorcerer:"
#define Word_princess "Princess:"
#define Word_fireball "Fireball:"
#define Param_health  "health:"
#define Param_damage  "damage:"

class Configuration
{
public:
	Configuration(const char S[]);
	~Configuration();
	int read_file();
	int read_params(int& Health, int& Damage);
private:
	std::ifstream File;
};
