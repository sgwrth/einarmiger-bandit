#include <chrono>
#include <random>
#include "numbergen.h"

numbergen::numbergen()
{
	std::mt19937 gen;
	gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
	number_generator = gen;
}

numbergen* numbergen::get_instance()
{
	if (instance != nullptr) {
		return instance;
	} else {
		return new numbergen();
	}
}

numbergen* numbergen::instance = nullptr;
