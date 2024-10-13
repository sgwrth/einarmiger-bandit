#include "player.h"
#include <iostream>

Player::Player(std::string name)
		: name{ name }
		, creditscore{ std::make_shared<Creditscore>() } {}

std::string Player::get_name()
{
	return name;
}

std::shared_ptr<Creditscore> Player::get_creditscore()
{
	return creditscore;
}

void Player::print_info()
{
	std::cout << "Spieler: " << get_name() << "\n";
	std::cout << "Guthaben: " << creditscore->compute_balance() << "\n";
}
