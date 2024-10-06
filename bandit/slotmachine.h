#pragma once
#include <array>
#include "creditscore.h"
#include "player.h"
#include "slot.h"

class slotmachine {
public:
	slotmachine();
	void insert_coin(player& player, std::shared_ptr<coin> coin);
	std::array<std::shared_ptr<slot>, 3> slots;
};

