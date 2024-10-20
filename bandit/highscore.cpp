#include "highscore.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "player.h"

Highscore::Highscore(std::string highscores_file)
		: highscores{ std::make_shared<std::vector<std::string>>()}
		, highscores_in{ highscores_file }
		, highscores_out{ highscores_file }
{
	std::cout << &(*highscores) << "\n";
}

void Highscore::read_old_highscores()
{
	std::cout << &(*highscores) << "\n";
	while (highscores_in) {
		std::string temp;
		std::getline(highscores_in, temp);
		highscores->push_back(temp);
	}
}

void Highscore::print_highscores()
{
	std::cout << &(*highscores) << "\n";
	for (std::string hs : *highscores) {
		std::cout << hs << "\n";
	}
}

void Highscore::write_old_highscores()
{
	std::cout << &(*highscores) << "\n";
	for (auto i = 0; i < highscores->size(); ++i) {
		if (i != (highscores->size() - 1)) {
			highscores_out << highscores->at(i) << "\n";
		}
		else {
			highscores_out << highscores->at(i);
		}
	}
}

void Highscore::append_new_highscore(Player& p, time_t time)
{
	std::cout << &(*highscores);
	highscores_out
			<< p.get_name()
			<< " - "
			<< p.get_creditscore()->get_balance()
			<< " - "
			<< std::ctime(&time);
}
