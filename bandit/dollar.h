#ifndef DOLLAR_H
#define DOLLAR_H
#include <string>
#include "coin.h"

class Dollar : public Coin {
public:
	Dollar();
	std::string get_name() override;
	int get_value() override;
private:
	std::string name;
	int value;
};

#endif
