#include "player.h"
#include <iostream>
#include <memory>
#include <vector>
#include "coin.h"
#include "creditscore.h"

Player::Player(std::string name)
		: name{ name }
		, creditscore{ std::make_shared<Creditscore>() } {}

std::string Player::get_name()
{
	return name;
}

void Player::insert_coin(std::shared_ptr<Coin> coin)
{
	creditscore->add_to_balance(coin);
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
