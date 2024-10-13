#include "slotmachine.h"
#include <memory>
#include "slot.h"

Slotmachine::Slotmachine()
		: slots{
				std::make_shared<Slot>(),
				std::make_shared<Slot>(),
				std::make_shared<Slot>()
		} {}

Slotmachine::Result Slotmachine::get_result()
{
	if (slots[2]->number == slots[1]->number
			&& slots[1]->number == slots[0]->number) {
		return Result::WIN;
	}
	if (slots[1]->number == slots[0]->number) {
		return Result::MONEY_BACK;
	}
	return Result::LOSE;
}
