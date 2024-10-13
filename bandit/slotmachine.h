#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H
#include <array>
#include <memory>
#include "player.h"
#include "coin.h"
#include "slot.h"

class Slotmachine {
public:
	Slotmachine();
	void insert_coin(Player& player, std::shared_ptr<Coin> coin);
	std::array<std::shared_ptr<Slot>, 3> slots;
	enum class Result { LOSE, MONEY_BACK, WIN };
	Result get_result();
};

#endif
