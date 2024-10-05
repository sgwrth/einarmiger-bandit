#pragma once
#include <vector>
#include "coin.h"

class creditscore {
public:
	creditscore();
	std::vector<coin> coins;
	long balance;
	void addToBalance(coin coin);
	long compute_balance();
};

