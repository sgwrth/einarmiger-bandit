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
	auto numbergen = Numbergen::get_instance();

	if (p1.get_creditscore()->get_balance() >= 200) {
		std::cout
			<< "Sie duerfen '20 Drehs' spielen!  Ihr 'Highscore' nach dem"
			<< " letzten Dreh wird gespeichert!  Los gehts!\n";
		int pulls_left{20};

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

	// Open input file "highscore.txt"
	std::ifstream old_hiscore_file(hiscore_filepath);

	// Copy "highscore.txt" --> "hiscore_temp.txt"
	std::ofstream hiscore_temp_file(hiscore_temp_filepath);
	Util::copy_file(old_hiscore_file, hiscore_temp_file);
	hiscore_temp_file.close();

	/**
	* Scoped the Highscore object to guarantee that it is destroyed
	* before calling the delete_file function on it, as a still live
	* object might be holding on to its fstream members, even when
	* they have been closed.
	*/
	{
		// Create highscore_table from "highscore.txt" (in) and "hiscore_temp.txt" (out)
		Highscore highscore_table(hiscore_filepath, hiscore_temp_filepath);

		// Populate highscores vector with data from "highscore.txt"
		highscore_table.read_old_highscores();

		// Copy highscores from "highscores" to "highscores_out"
		highscore_table.write_old_highscores();

		// highscore_table.print_highscores();

		time_t time
			= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		time_t* time_ptr = &time;
		highscore_table.append_new_highscore(p1, time_ptr);
		std::cout << "Thanks for playing!\n";

		// Closing files
		old_hiscore_file.close();
		highscore_table.highscores_in.close();
		highscore_table.highscores_out.close();
	}

	// Delete "highscore.txt"
	Util::delete_file(hiscore_filepath);

	// Rename "hiscore_temp.txt" to "highscore.txt"
	Util::rename_file(hiscore_temp_filepath, hiscore_filename);


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