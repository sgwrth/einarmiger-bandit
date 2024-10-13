#include <iostream>
#include "Coin.h"
#include "Dollar.h"
#include "Messages.h"
#include "Numbergen.h"
#include "Player.h"
#include "slotmachine.h"

int main()
{
	Slotmachine machine;
	Messages messages;
	std::cout << messages.PROMPT_FOR_NAME;
	std::string player_name{};
	std::cin >> player_name;
	Player p1(player_name);
	int number_of_dollar_coins{ 0 };
	std::cout << messages.PROMPT_FOR_PAYMENT;
	while (p1.get_creditscore()->compute_balance() <= 0) {
		std::cout << "[f] 5 Dollar\n";
		std::cout << "[z] 10 Dollar\n";
		char option{};
		std::cin >> option;
		switch (option) {
		case 'f': {
			std::shared_ptr<Coin> c = std::make_shared<Dollar>();
			for (auto i = 0; i < 5; ++i) {
				p1.insert_coin(c);
			}
			break;
		}
		case 'z': {
			std::shared_ptr<Coin> c = std::make_shared<Dollar>();
			for (auto i = 0; i < 10; ++i) {
				p1.insert_coin(c);
			}
			break;
		}
		default:
			std::cout << messages.ERROR_INVALID_INPUT;
			break;
		}
	}
	p1.get_creditscore()->add_amount_to_balance(p1.get_creditscore()->compute_balance());
	p1.print_info();
	std::cout << p1.get_creditscore()->get_balance() << "\n";

	auto numbergen = Numbergen::get_instance();

	char pull{};
	while (pull != 'n' && p1.get_creditscore()->get_balance() >= 100) {
		pull = 'x';
		for (auto i = 0; i < machine.slots.size(); ++i) {
			machine.slots[i]->number = numbergen->number_generator() % 10;
		}
		std::cout << "[" << machine.slots[0]->number << "] ";
		std::cout << "[" << machine.slots[1]->number << "] ";
		std::cout << "[" << machine.slots[2]->number << "]\n";

		p1.get_creditscore()->process_result(machine);
		std::cout << "Guthaben: " << p1.get_creditscore()->get_balance() << "\n";

		if (p1.get_creditscore()->get_balance() < 100) {
			std::cout << "Sorry, nicht genug Guthaben :(\n";
			break;
		}

		while (pull != 'y' && pull != 'n') {
			std::cout << "Nochmal ziehen? [y/n]\n";
			std::cin >> pull;
			if (pull != 'y' && pull != 'n') {
				std::cout << messages.ERROR_INVALID_INPUT;
			}
		}
	}

	return 0;
}