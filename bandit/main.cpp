#include <chrono>
#include <ctime>
#include <fstream>
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
		std::cout << "[1] 5 Dollar\n";
		std::cout << "[2] 10 Dollar\n";
		std::cout << "[3] 20 Dollar\n";
		char option{};
		std::cin >> option;
		switch (option) {
		case '1': {
			std::shared_ptr<Coin> c = std::make_shared<Dollar>();
			for (auto i = 0; i < 5; ++i) {
				p1.insert_coin(c);
			}
			break;
		}
		case '2': {
			std::shared_ptr<Coin> c = std::make_shared<Dollar>();
			for (auto i = 0; i < 10; ++i) {
				p1.insert_coin(c);
			}
			break;
		}
		case '3': {
			std::shared_ptr<Coin> c = std::make_shared<Dollar>();
			for (auto i = 0; i < 20; ++i) {
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

	if (p1.get_creditscore()->get_balance() >= 200) {
		std::cout << "Sie duerfen '20 Drehs' spielen!  Ihr 'Highscore' nach dem letzten "
			"Dreh wird gespeichert!  Los gehts!\n";
		int pulls_left{ 20 };
		while (pulls_left > 0) {
			machine.spin_slots(numbergen);
			machine.print_slot_numbers();
			p1.get_creditscore()->process_result(machine);
			std::cout << "Guthaben: " << p1.get_creditscore()->get_balance() << "\n";
			std::cout << "Press any key to continue!\n";
			std::cin.clear();
			std::cin.ignore();
			--pulls_left;
		}

		auto highscores = std::make_shared<std::vector<std::string>>();
		std::ifstream highscore_in{ "./highscore.txt" };

		while (highscore_in) {
			std::string temp;
			std::getline(highscore_in, temp);
			highscores->push_back(temp);
		}

		// control output
		for (std::string hs : *highscores) {
			std::cout << hs << "\n";
		}

		std::ofstream highscore_out{ "./highscore.txt" };
		for (auto i = 0; i < highscores->size(); ++i) {
			if (i != (highscores->size() - 1)) {
				highscore_out << highscores->at(i) << "\n";
			}
			else {
				highscore_out << highscores->at(i);
			}
		}

		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		highscore_out
				<< p1.get_name()
				<< " - "
				<< p1.get_creditscore()->get_balance()
				<< " - "
				<< std::ctime(&time);
		std::cout << "Thanks for playing!\n";
	}

	char pull{};
	while (pull != 'n' && p1.get_creditscore()->get_balance() >= 100) {
		pull = 'x';
		machine.spin_slots(numbergen);
		machine.print_slot_numbers();
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