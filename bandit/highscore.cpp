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
		: highscores{std::make_shared<std::vector<std::string>>()}
		, highscores_struct{std::make_shared<std::vector<Hiscore_entry>>()}
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
	int result = strftime(buff, sizeof(buff), "%Y.%m.%d %H:%M", &time_tm);

	if (result == 0) {
		std::cout << "some strftime error\n";
		return;
	}

	highscores_out
		<< player.get_creditscore()->get_balance()
		<< ' '
		<< buff
		<< ' '
		<< player.get_name()
		<< '\n';
}


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

void Highscore::read_hiscores_from_filestream()
{

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
	time_t time_t = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now()
	);
	struct tm time_tm;
	errno_t err = localtime_s(&time_tm, &time_t);

	if (err != 0) {
		std::cout << "some localtime_s error\n";
	}

	char date[100];
	char time[100];

	int date_result = strftime(date, sizeof(date), "%Y.%m.%d", &time_tm);
	int time_result = strftime(time, sizeof(time), "%H:%M", &time_tm);

	if (date_result == 0 || time_result == 0) {
		std::cout << "some strftime error\n";
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
	highscores_struct->push_back(create_hiscore_struct(player));
	std::vector<Hiscore_entry> sorted_hiscores
		= Highscore::sort_hiscores(*highscores_struct);
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
