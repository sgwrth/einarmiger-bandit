#include "slotmachine.h"
#include <iostream>
#include <memory>
#include "coin.h"
#include "dollar.h"
#include "messages.h"
#include "numbergen.h"
#include "player.h"
#include "slot.h"

Slotmachine::Slotmachine()
	: slots{
		std::make_shared<Slot>(),
		std::make_shared<Slot>(),
		std::make_shared<Slot>()
	}
{}

void Slotmachine::offer_to_buy_credits(Player& player) {
	char option{};
	std::cout << "[1] 5 Dollar\n";
	std::cout << "[2] 10 Dollar\n";
	std::cout << "[3] 20 Dollar\n";
	std::cin >> option;
	std::cin.clear();
	std::cin.ignore();
	Messages messages;

	switch (option) {
	case '1': {
		std::shared_ptr<Coin> c = std::make_shared<Dollar>();
		for (auto i = 0; i < 5; ++i) {
			player.insert_coin(c);
		}
		break;
	}
	case '2': {
		std::shared_ptr<Coin> c = std::make_shared<Dollar>();
		for (auto i = 0; i < 10; ++i) {
			player.insert_coin(c);
		}
		break;
	}
	case '3': {
		std::shared_ptr<Coin> c = std::make_shared<Dollar>();
		for (auto i = 0; i < 20; ++i) {
			player.insert_coin(c);
		}
		break;
	}
	default:
		std::cout << messages.ERROR_INVALID_INPUT;
		break;
	}
}

Slotmachine::Result Slotmachine::get_result()
{
	int no_1 = slots[0]->number;
	int no_2 = slots[1]->number;
	int no_3 = slots[2]->number;
	bool three_of_a_kind = no_3 == no_2 && no_2 == no_1;
	bool first_two_of_a_kind = no_2 == no_1;

	if (three_of_a_kind) {
		return Result::WIN;
	}

	if (first_two_of_a_kind) {
		return Result::MONEY_BACK;
	}

	return Result::LOSE;
}

void Slotmachine::spin_slots(std::shared_ptr<Numbergen> numbergen)
{
	for (auto i = 0; i < slots.size(); ++i) {
		slots[i]->number = numbergen->number_generator() % 10;
	}
}

void Slotmachine::print_slot_numbers()
{
	std::cout << '\n';
	for (auto i = 0; i < slots.size(); ++i) {
		std::cout << '[' << slots[i]->number << ']';
		auto space_or_break = (i < (slots.size() - 1)) ? ' ' : '\n';
		std::cout << space_or_break;
	}
}
