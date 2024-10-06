#pragma once
#include <vector>
#include "coin.h"

class creditscore {
public:
	std::vector<coin*> coins;
	std::vector<coin*>& get_coins();
	void add_to_balance(std::vector<coin*>& coins, coin& coin);
	long compute_balance();
};

