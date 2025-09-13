#include "highscore.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>
#include "player.h"

Highscore::Highscore(std::string highscores_file)
		: highscores{std::make_shared<std::vector<std::string>>()}
		, highscores_in{highscores_file}
		, highscores_out{highscores_file}
{}

void Highscore::read_old_highscores()
{
	while (highscores_in) {
		std::string temp;
		std::getline(highscores_in, temp);
		highscores->push_back(temp);
	}
}

void Highscore::print_highscores()
{
	for (std::string hs : *highscores) {
		std::cout << hs << "\n";
	}
}

void Highscore::write_old_highscores()
{
	auto latest_highscore_idx = highscores->size() - 1;

	for (auto i = 0; i < highscores->size(); ++i) {
		if (i != latest_highscore_idx) {
			highscores_out << highscores->at(i) << "\n";
		} else {
			highscores_out << highscores->at(i);
		}
	}
}

void Highscore::append_new_highscore(Player& p, time_t* time)
{
	char buff[100];
	struct tm time_tm;
	errno_t err = localtime_s(&time_tm, time);

	if (err != 0) {
		std::cout << "some localtime_s error\n";
		return;
	}

	int result = strftime(buff, sizeof(buff), "%c", &time_tm);

	if (result == 0) {
		std::cout << "some strftime error\n";
		return;
	}

	highscores_out
		<< p.get_name()
		<< " - "
		<< p.get_creditscore()->get_balance()
		<< " - "
		<< buff
		<< "\n";
}
