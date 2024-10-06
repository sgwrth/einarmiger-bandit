#include <iostream>
#include "creditscore.h"

std::vector<std::shared_ptr<coin>>& creditscore::get_coins()
{
	return coins;
}

void creditscore::add_to_balance(
		std::vector<std::shared_ptr<coin>>& coins,
		std::shared_ptr<coin> coin
) {
	coins.push_back(coin);
}

long creditscore::compute_balance()
{
	long total_credit{ 0 };
	if (coins.size() == 0) {
		return 0;
	}
	for (auto i = 0; i < coins.size(); ++i) {
		total_credit += coins[i]->get_value();
	}
	return total_credit;
}
