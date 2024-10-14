#ifndef NUMBERGEN_H
#define NUMBERGEN_H
#include <memory>
#include <random>

class Numbergen {
public:
	static std::shared_ptr<Numbergen> get_instance();
	std::mt19937 number_generator;
	Numbergen();
private:
	static std::shared_ptr<Numbergen> instance;
};

#endif
