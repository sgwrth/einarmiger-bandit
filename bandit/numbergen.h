#ifndef NUMBERGEN_H
#define NUMBERGEN_H
#include <random>

class Numbergen {
public:
	static Numbergen* get_instance();
	std::mt19937 number_generator;
private:
	Numbergen();
	static Numbergen* instance;
};

#endif
