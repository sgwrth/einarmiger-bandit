#pragma once
#include "creditscore.h"
#include "player.h"

class slotmachine {
public:
	void insert_coin(player& player, std::shared_ptr<coin> coin);
};

