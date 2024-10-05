#pragma once
#include <string>
#include "creditscore.h"

class player {
public:
	player(std::string name);
	std::string name;
	creditscore creditscore;
};

