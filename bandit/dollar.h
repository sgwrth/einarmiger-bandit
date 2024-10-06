#pragma once
#include "coin.h"

class dollar : public coin {
public:
	dollar();
	std::string get_name() override;
	int get_value() override;
private:
	std::string name;
	int value;
};

