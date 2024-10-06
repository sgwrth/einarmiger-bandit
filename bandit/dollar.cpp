#include "dollar.h"

dollar::dollar() : name{ "Dollar" }, value{ 100 } {}

std::string dollar::get_name()
{
	return name;
}

int dollar::get_value()
{
	return value;
}

//dollar::~dollar() {}
