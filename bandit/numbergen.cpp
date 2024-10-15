#include "numbergen.h"
#include <chrono>
#include <memory>
#include <random>

Numbergen::Numbergen()
{
	std::mt19937 gen;
	gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
	number_generator = gen;
}

std::shared_ptr<Numbergen> Numbergen::instance = nullptr;

//std::shared_ptr<Numbergen> Numbergen::instance = get_instance();

std::shared_ptr<Numbergen> Numbergen::get_instance()
{
	if (instance != nullptr) {
		return instance;
	} else {
		return std::make_shared<Numbergen>();
	}
}
