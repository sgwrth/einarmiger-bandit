#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H
#include <array>
#include <memory>
#include "coin.h"
#include "numbergen.h"
#include "slot.h"

class Slotmachine {
public:
	Slotmachine();
	std::array<std::shared_ptr<Slot>, 3> slots;
	enum class Result { LOSE, MONEY_BACK, WIN };
	Result get_result();
	void spin_slots(std::shared_ptr<Numbergen> numbergen);
	void print_slot_numbers();
};

#endif
