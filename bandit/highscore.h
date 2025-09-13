#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class Player;

class Highscore
{
public:
	Highscore(std::string highscores_file);
	std::shared_ptr<std::vector<std::string>> highscores;
	std::ifstream highscores_in;
	std::ofstream highscores_out;
	void read_old_highscores();
	void print_highscores();
	void write_old_highscores();
	void append_new_highscore(Player& p, time_t* time);
};

#endif
