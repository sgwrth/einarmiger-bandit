#include <fstream>
#include <iostream>
#include "coin.h"
#include "dollar.h"
#include "highscore.h"
#include "messages.h"
#include "numbergen.h"
#include "player.h"
#include "slotmachine.h"
#include "util.h"

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

	p1.get_creditscore()
		->add_amount_to_balance(p1.get_creditscore()->compute_balance());
	p1.print_info();
	std::cout << p1.get_creditscore()->get_balance() << "\n";

	if (p1.get_creditscore()->get_balance() >= 200) {
		std::cout
			<< "Sie duerfen '20 Drehs' spielen!  Ihr 'Highscore' nach dem"
			<< " letzten Dreh wird gespeichert!  Los gehts!\n";
		int pulls_left{20};

		auto numbergen = Numbergen::get_instance();
		while (pulls_left > 0) {
			machine.spin_slots(numbergen);
			machine.print_slot_numbers();
			p1.get_creditscore()->process_result(machine);
			std::cout
				<< "Guthaben: "
				<< p1.get_creditscore()->get_balance()
				<< "\n";
			std::cout << "Press any key to continue!\n";
			std::cin.clear();
			std::cin.ignore();
			--pulls_left;

			if (p1.get_creditscore()->get_balance() < 100) {
				std::cout << "Sorry, nicht genug Guthaben :(\n";
				break;
			}
		}
	}

	const std::string hiscore_filepath = "./highscore.txt";
	const std::string hiscore_filename = "highscore.txt";
	const std::string hiscore_temp_filepath = "./hiscore_temp.txt";
	const std::string hiscore_temp_filename = "hiscore_temp.txt";

	Highscore highscore_table(hiscore_filepath, hiscore_temp_filepath);
	highscore_table.read_old_highscores();
	highscore_table.write_old_highscores();
	highscore_table.append_new_highscore(p1);
	highscore_table.highscores_in.close();
	highscore_table.highscores_out.close();
	Util::delete_file(hiscore_filepath);
	Util::rename_file(hiscore_temp_filepath, hiscore_filename);
	std::cout << "Thanks for playing!\n";

	/*
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
	*/

	return 0;
}