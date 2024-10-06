#include <iostream>
#include "player.h"

player::player(std::string name) : name{ name } {}

std::string player::get_name()
{
	return name;
}

creditscore& player::get_creditscore()
{
	return creditscore;
}

void player::print_info()
{
	std::cout << "Spieler: " << get_name() << "\n";
	std::cout << "Guthaben: " << get_creditscore().compute_balance() << "\n";
}
