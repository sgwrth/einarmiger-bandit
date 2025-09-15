#include "player.h"
#include <iostream>
#include <memory>
#include <vector>
#include "coin.h"
#include "creditscore.h"

Player::Player(std::string name)
	: name{ name }
	, creditscore{ std::make_shared<Creditscore>() } {}

std::string Player::get_name() const
{
	return name;
}

void Player::insert_coin(std::shared_ptr<Coin> coin)
{
	creditscore->add_to_balance(coin);
}

std::shared_ptr<Creditscore> Player::get_creditscore() const
{
	return creditscore;
}

void Player::print_name() const
{
	std::cout << get_name() << "\n";
}

void Player::print_balance()
{
	std::cout << creditscore->get_balance() << "\n";
}
