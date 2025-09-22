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
	Util::print_msg(messages.PROMPT_FOR_NAME);
	Player p1(Util::get_str_input());
	Util::print_msg(messages.PROMPT_FOR_PAYMENT);

	while (p1.get_creditscore()->compute_balance() <= 0) {
		machine.offer_to_buy_credits(p1);
	}

	p1.get_creditscore()
		->add_amount_to_balance(p1.get_creditscore()->compute_balance());
	p1.print_name();
	p1.print_balance();

	if (p1.get_creditscore()->get_balance() >= 200) {
		Util::print_msg(messages.MSG_START_GAME);
		std::cin.get();
		int pulls_left{ 20 };
		auto numbergen = Numbergen::get_instance();

		while (pulls_left > 0) {
			machine.spin_slots(numbergen);
			machine.print_slot_numbers();
			p1.get_creditscore()->process_result(machine);

			if (p1.get_creditscore()->get_balance() < 100) {
				Util::print_msg(messages.MSG_NOT_ENOUGH_CREDITS);
				break;
			}

			Util::print_msg(messages.MSG_BALANCE);
			p1.print_balance();
			Util::print_msg(messages.MSG_ANY_KEY_TO_CONT);
			std::cin.get();
			--pulls_left;
		}
	}

	if (p1.get_creditscore()->get_balance() <= 0) {
		Util::print_msg(messages.MSG_NO_HISCORE);
		return 0;
	}

	const std::string hiscore_filename = "highscores.txt";
	const std::string hiscore_filepath = "./" + hiscore_filename;
	const std::string hiscore_temp_filename = "hiscore_temp.txt";
	const std::string hiscore_temp_filepath = "./" + hiscore_temp_filename;
	Highscore highscore_table(hiscore_filepath, hiscore_temp_filepath);
	//highscore_table.read_old_highscores();
	//highscore_table.write_old_highscores();
	//highscore_table.append_new_highscore(p1);
	highscore_table.load_hiscores_into_struct();
	highscore_table.write_hiscores_to_file();
	highscore_table.highscores_in.close();
	highscore_table.highscores_out.close();
	Util::delete_file(hiscore_filepath);
	Util::rename_file(hiscore_temp_filepath, hiscore_filename);
	Util::print_msg(messages.MSG_THANKS_FOR_PLAYING);

	return 0;
}