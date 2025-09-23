#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <fstream>
#include <memory>
#include <string>
#include <vector>

struct Hiscore_entry;
class Player;

class Highscore
{
public:
	Highscore(std::string highscores_file_in, std::string highscores_file_out);
	std::shared_ptr<std::vector<std::string>> highscores;
	std::shared_ptr<std::vector<Hiscore_entry>> highscores_struct;
	std::ifstream highscores_in;
	std::ofstream highscores_out;
	static Hiscore_entry read_hiscore(const std::string& hiscore);
	static std::string write_hiscore(const Hiscore_entry& hiscore);
	static std::vector<Hiscore_entry> sort_hiscores(
		std::vector<Hiscore_entry>& hiscores
	);
	void load_hiscores_into_struct();
	static Hiscore_entry create_hiscore_struct(Player& player);
	void add_hiscore_to_vector(Player& player);
	void write_hiscores_to_file();
	void print_hiscores() const;
};

#endif
