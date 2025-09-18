#ifndef HISCORE_ENTRY_H
#define HISCORE_ENTRY_H
#include <string>

struct Hiscore_entry {
	int score;
	std::string date;
	std::string time;
	std::string player;
};

#endif
