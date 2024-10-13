#include "creditscore.h"

Creditscore::Creditscore() : balance{ 0 }, coins{} {}

std::vector<std::shared_ptr<Coin>>& Creditscore::get_coins()
{
	return coins;
}

void Creditscore::set_balance(long amount)
{
	balance = balance + amount;
}

void Creditscore::add_to_balance(
		std::vector<std::shared_ptr<Coin>>& coins,
		std::shared_ptr<Coin> coin
) {
	coins.push_back(coin);
}

long Creditscore::compute_balance()
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

void Creditscore::process_result(Slotmachine& machine)
{
	if (machine.get_result() == Slotmachine::Result::WIN) {
		set_balance(1000);
	}
	if (machine.get_result() == Slotmachine::Result::MONEY_BACK) {
		return;
	}
	if (machine.get_result() == Slotmachine::Result::LOSE) {
		set_balance(-100);
	}
}
