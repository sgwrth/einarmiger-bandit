#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H
#include <array>
#include <memory>
#include "coin.h"
#include "slot.h"

class Slotmachine {
public:
	Slotmachine();
	std::array<std::shared_ptr<Slot>, 3> slots;
	enum class Result { LOSE, MONEY_BACK, WIN };
	Result get_result();
};

#endif
