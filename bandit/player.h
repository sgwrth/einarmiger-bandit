#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include "creditscore.h"

class Player {
public:
	Player(std::string name);
	std::string get_name();
	std::shared_ptr<Creditscore> get_creditscore();
	void print_info();
private:
	std::string name;
	std::shared_ptr<Creditscore> creditscore;
};

#endif
