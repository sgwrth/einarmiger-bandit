#pragma once
#include <random>

class numbergen {
public:
	static numbergen* get_instance();
	std::mt19937 number_generator;
private:
	numbergen();
	static numbergen* instance;
};

