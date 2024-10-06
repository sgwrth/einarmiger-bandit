#pragma once
#include <vector>
#include "coin.h"

class creditscore {
public:
	std::vector<std::shared_ptr<coin>> coins;
	std::vector<std::shared_ptr<coin>>& get_coins();
	void add_to_balance(
			std::vector<std::shared_ptr<coin>>& coins,
			std::shared_ptr<coin> coin
	);
	long compute_balance();
};

