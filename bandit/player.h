#pragma once
#include <string>
#include "creditscore.h"

class player {
public:
	player(std::string name);
	std::string get_name();
	creditscore& get_creditscore();
	void print_info();
private:
	std::string name;
	creditscore creditscore;
};

