#pragma once
#include "coin.h"

class dollar : public coin {
public:
	dollar(std::string name, int value);
	std::string name;
	int value;
};

