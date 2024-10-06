#include <iostream>
#include <string>
#include "dollar.h"
#include "messages.h"
#include "numbergen.h"
#include "slotmachine.h"

int main()
{
	slotmachine machine;
	messages messages;
	std::cout << messages.PROMPT_FOR_NAME;
	std::string player_name{};
	std::cin >> player_name;
	player p1(player_name);
	int number_of_dollar_coins{ 0 };
	std::cout << messages.PROMPT_FOR_PAYMENT;
	while (p1.get_creditscore().compute_balance() <= 0) {
		std::cout << "[f] 5 Dollar\n";
		std::cout << "[z] 10 Dollar\n";
		char option{};
		std::cin >> option;
		switch (option) {
		case 'f': {
			std::shared_ptr<coin> c = std::make_shared<dollar>();
			for (auto i = 0; i < 5; ++i) {
				machine.insert_coin(p1, c);
			}
			break;
		}
		case 'z': {
			std::shared_ptr<coin> c = std::make_shared<dollar>();
			for (auto i = 0; i < 10; ++i) {
				machine.insert_coin(p1, c);
			}
			break;
		}
		default:
			std::cout << messages.ERROR_INVALID_INPUT;
			break;
		}
	}
	p1.print_info();

	auto numbergen = numbergen::get_instance();
	std::cout << numbergen->number_generator() % 10 << "\n";

	std::cout << machine.slots[0]->number << "\n";
	std::cout << machine.slots[1]->number << "\n";
	std::cout << machine.slots[2]->number << "\n";

	return 0;
}