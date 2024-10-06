#include <iostream>
#include "creditscore.h"

std::vector<coin*>& creditscore::get_coins()
{
	return coins;
}

void creditscore::add_to_balance(std::vector<coin*>& coins, coin& coin)
{
	coins.push_back(&coin);
}

long creditscore::compute_balance()
{
	long total_credit{ 0 };
	if (coins.size() == 0) {
		return 0;
	}
	for (size_t i = 0; i < coins.size(); ++i) {
		total_credit += coins[i]->get_value();
	}
	return total_credit;
}
