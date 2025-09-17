#include "highscore.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>
#include "player.h"

Highscore::Highscore(std::string filepath_in, std::string filepath_out)
		: highscores{std::make_shared<std::vector<std::string>>()}
		, highscores_in{filepath_in}
		, highscores_out(filepath_out, std::ios::app)
{}

void Highscore::read_old_highscores()
{
	std::string line;
	while (std::getline(highscores_in, line)) {
		highscores->push_back(line);
	}
}

void Highscore::print_highscores() const
{
	for (const auto& hiscore : *highscores) {
		std::cout << hiscore << "\n";
	}
}

void Highscore::write_old_highscores()
{
	for (const auto& hiscore : *highscores) {
		highscores_out << hiscore << "\n";
	}
}

void Highscore::append_new_highscore(Player& player)
{
	time_t time
		= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm time_tm;
	errno_t err = localtime_s(&time_tm, &time);

	if (err != 0) {
		std::cout << "some localtime_s error\n";
		return;
	}

	char buff[100];
	int result = strftime(buff, sizeof(buff), "%c", &time_tm);

	if (result == 0) {
		std::cout << "some strftime error\n";
		return;
	}

	highscores_out
		<< player.get_creditscore()->get_balance()
		<< " - "
		<< buff
		<< " - "
		<< player.get_name()
		<< "\n";
}
