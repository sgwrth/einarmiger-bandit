#include "slotmachine.h"

Slotmachine::Slotmachine()
		: slots{
				std::make_shared<Slot>(),
				std::make_shared<Slot>(),
				std::make_shared<Slot>()
		} {}

void Slotmachine::insert_coin(Player& player, std::shared_ptr<Coin> coin)
{
	std::vector<std::shared_ptr<Coin>> coins = player.get_creditscore()->get_coins();
	player.get_creditscore()->add_to_balance(coins, coin);
}

Slotmachine::Result Slotmachine::get_result()
{
	if (slots[2]->number == slots[1]->number
			&& slots[1]->number == slots[0]->number) {
		return Result::WIN;
	}
	if (slots[2]->number == slots[1]->number) {
		return Result::MONEY_BACK;
	}
	return Result::LOSE;
}
