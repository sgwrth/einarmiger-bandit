#include <iostream>
#include "dollar.h"
#include "slotmachine.h"

int main()
{
	std::cout << "hello, world!\n";

	slotmachine machine;
	std::cout << "Spielernamen eingeben!\n";
	std::string player_name{ "" };
	std::cin >> player_name;
	player p1(player_name);
	int number_of_dollar_coins{ 0 };
	std::cout << "Ihr Guthaben ihr leer.  Wieviele Dollar moechten Sie einwerfen?\n";
	while (p1.get_creditscore().compute_balance() <= 0) {
		std::cout << "[f] 5 Dollar\n";
		std::cout << "[z] 10 Dollar\n";
		char option{ '0' };
		std::cin >> option;
		switch (option) {
		case 'f': {
			coin* c = new dollar();
			for (auto i = 0; i < 5; ++i) {
				machine.insert_coin(p1, *c);
			}
			break;
		}
		case 'z': {
			coin* c = new dollar();
			for (auto i = 0; i < 10; ++i) {
				machine.insert_coin(p1, *c);
			}
			break;
		}
		default:
			std::cout << "Ungueltige Eingabe!\n";
			break;
		}
	}
	p1.print_info();

	return 0;
}