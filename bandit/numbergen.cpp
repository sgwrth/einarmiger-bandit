#include "numbergen.h"
#include <chrono>
#include <random>

Numbergen::Numbergen()
{
	std::mt19937 gen;
	gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
	number_generator = gen;
}

Numbergen* Numbergen::instance = nullptr;

Numbergen* Numbergen::get_instance()
{
	if (instance != nullptr) {
		return instance;
	} else {
		return new Numbergen();
	}
}
