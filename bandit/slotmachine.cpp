#include "slotmachine.h"
#include <iostream>
#include <memory>
#include "numbergen.h"
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

void Slotmachine::spin_slots(std::shared_ptr<Numbergen> numbergen)
{
	for (auto i = 0; i < slots.size(); ++i) {
		slots[i]->number = numbergen->number_generator() % 10;
	}
}

void Slotmachine::print_slot_numbers()
{
	for (auto i = 0; i < slots.size(); ++i) {
		std::cout << "[" << slots[i]->number << "]";
		auto space_or_break = (i < (slots.size() - 1)) ? " " : "\n";
		std::cout << space_or_break;
	}
}
