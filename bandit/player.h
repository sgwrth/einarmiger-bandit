#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include "creditscore.h"

class Coin;

class Player {
public:
	Player(std::string name);
	std::string get_name() const;
	void insert_coin(std::shared_ptr<Coin> coin);
	std::shared_ptr<Creditscore> get_creditscore() const;
	void print_name() const;
	void print_balance();
private:
	std::string name;
	std::shared_ptr<Creditscore> creditscore;
};

#endif
