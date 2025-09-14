#include "highscore.h"
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


Highscore::~Highscore() {
	if (highscores_in.is_open()) {
		highscores_in.close();
	}
	if (highscores_out.is_open()) {
		highscores_out.close();
	}
}

void Highscore::read_old_highscores()
{
	std::string line;
	while (std::getline(highscores_in, line)) {
		std::cout << "adding to highscores: " << line << "\n";
		highscores->push_back(line);
	}
}

void Highscore::print_highscores()
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
