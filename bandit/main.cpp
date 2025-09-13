#include <chrono>
#include <fstream>
#include <iostream>
#include "coin.h"
#include "dollar.h"
#include "highscore.h"
#include "messages.h"
#include "numbergen.h"
#include "player.h"
#include "slotmachine.h"

int main()
{
	Slotmachine machine;
	Messages messages;
	std::cout << messages.PROMPT_FOR_NAME;
	std::string player_name{};
	std::cin >> player_name;
	Player p1(player_name);
	int number_of_dollar_coins{};
	std::cout << messages.PROMPT_FOR_PAYMENT;

	while (p1.get_creditscore()->compute_balance() <= 0) {
		machine.offer_to_buy_credits(p1);
	}

	p1.get_creditscore()->add_amount_to_balance(p1.get_creditscore()->compute_balance());
	p1.print_info();
	std::cout << p1.get_creditscore()->get_balance() << "\n";

	auto numbergen = Numbergen::get_instance();

	if (p1.get_creditscore()->get_balance() >= 200) {
		std::cout << "Sie duerfen '20 Drehs' spielen!  Ihr 'Highscore' nach dem letzten "
			"Dreh wird gespeichert!  Los gehts!\n";
		int pulls_left{20};

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
		std::cout << &(*highscores) << "\n";

		Highscore hi_score("./highscore.txt");
		hi_score.read_old_highscores();
		hi_score.print_highscores();
		hi_score.write_old_highscores();

		std::ifstream highscores_in{ "./highscore.txt" };

		while (highscores_in) {
			std::string temp;
			std::getline(highscores_in, temp);
			highscores->push_back(temp);
		}

		// control output
		for (std::string hs : *highscores) {
			std::cout << hs << "\n";
		}

		std::ofstream highscores_out{ "./highscore.txt" };

		for (auto i = 0; i < highscores->size(); ++i) {
			if (i != (highscores->size() - 1)) {
				highscores_out << highscores->at(i) << "\n";
			}
			else {
				highscores_out << highscores->at(i);
			}
		}

		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		hi_score.append_new_highscore(p1, time);

		hi_score.highscores_out
			<< p1.get_name()
			<< " - "
			<< p1.get_creditscore()->get_balance()
			<< " - ";

		std::cout << "Thanks for playing!\n";
	}

	char pull{};

	/*
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
	*/

	return 0;
}