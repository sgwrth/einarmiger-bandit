#include <iostream>
#include "creditscore.h"

creditscore::creditscore()
{
	std::cout << "creditscore created [" << &coins << ", size: " << coins.size() << "]\n";
}

std::vector<coin*>& creditscore::get_coins()
{
	return coins;
}

void creditscore::add_to_balance(std::vector<coin*>& coins, coin& coin)
{
	std::cout << "add_to_balance: " << &coins << "\n";
	coins.push_back(&coin);
}

long creditscore::compute_balance()
{
	long total_credit{ 0 };
	std::cout << "compute_balance: " << &coins << "\n";
	std::cout << "coins.size: " << coins.size() << "\n";
	if (coins.size() == 0) {
		return 0;
	}
	for (auto i = 0; i < coins.size(); ++i) {
		std::cout << "inside for loop\n";
		total_credit += coins[i]->get_value();
	}
	return total_credit;
}
