#include "highscore.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>
#include "hiscore_entry.h"
#include "player.h"
#include "util.h"

Highscore::Highscore(std::string filepath_in, std::string filepath_out)
	: highscores_struct{std::make_shared<std::vector<Hiscore_entry>>()}
	, highscores_in{filepath_in}
	, highscores_out(filepath_out, std::ios::app)
{}

Hiscore_entry Highscore::read_hiscore(const std::string& hiscore)
{
	std::vector<std::string> tokens = Util::split(hiscore, ' ');

	return Hiscore_entry{
		std::stoi(tokens[0]),
		tokens[1],
		tokens[2],
		tokens[3]
	};
}

std::string Highscore::write_hiscore(const Hiscore_entry& hiscore)
{
	std::string score, date, time, player;
	score = std::to_string(hiscore.score);
	date = hiscore.date;
	time = hiscore.time;
	player = hiscore.player;
	return score + ' ' + date + ' ' + time + ' ' + player;
}

std::vector<Hiscore_entry> Highscore::sort_hiscores(
		std::vector<Hiscore_entry>& hiscores
)
{
	std::vector<Hiscore_entry> sorted_hiscores;

	while (!hiscores.empty()) {
		auto max_hiscore{ hiscores.begin() };

		for (auto it = hiscores.begin(); it != hiscores.end(); ++it) {
			if (it->score > max_hiscore->score) {
				max_hiscore = it;
			}
		}

		sorted_hiscores.push_back(*max_hiscore);
		hiscores.erase(max_hiscore);
	}

	return sorted_hiscores;
}

void Highscore::load_hiscores_into_struct()
{
	std::string line;

	while (std::getline(highscores_in, line)) {
		highscores_struct->push_back(read_hiscore(line));
	}
}

Hiscore_entry Highscore::create_hiscore_struct(Player& player)
{
	struct tm time_tm = Util::get_time_tm();
	if (time_tm.tm_year == 0) {
		std::cerr << "some localtime_s error\n";
	}

	char date[100];
	char time[100];
	int date_result = strftime(date, sizeof(date), "%Y.%m.%d", &time_tm);
	int time_result = strftime(time, sizeof(time), "%H:%M", &time_tm);

	if (date_result == 0 || time_result == 0) {
		std::cerr << "some strftime error\n";
	}

	return Hiscore_entry{
		player.get_creditscore()->get_balance(),
		date,
		time,
		player.get_name()
	};
}

void Highscore::add_hiscore_to_vector(Player& player)
{
	highscores_struct->push_back(Highscore::create_hiscore_struct(player));
	auto sorted_hiscores = Highscore::sort_hiscores(*highscores_struct);
	highscores_struct
		= std::make_shared<std::vector<Hiscore_entry>>(sorted_hiscores);

	if (highscores_struct->size() == 11) {
		highscores_struct->pop_back();
	}
}

void Highscore::write_hiscores_to_file()
{
	for (const auto& hiscore : *highscores_struct) {
		highscores_out << write_hiscore(hiscore) << '\n';
	}
}

void Highscore::print_hiscores() const
{
	for (const auto& hiscore : *highscores_struct) {
		std::cout << Highscore::write_hiscore(hiscore) << '\n';
	}
}
