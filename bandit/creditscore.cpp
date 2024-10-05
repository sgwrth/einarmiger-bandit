#include "coin.h"
#include "creditscore.h"

creditscore::creditscore() : coins{ {} }, balance{ 0 } {}

void creditscore::addToBalance(coin coin)
{
	coins.push_back(coin);
}

long creditscore::compute_balance()
{
	long total_credit{ 0 };
	for (coin c : coins) {
		total_credit += c.value;
	}
	return total_credit;
}
