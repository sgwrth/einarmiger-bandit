#include "dollar.h"
#include <string>

Dollar::Dollar() : name{ "Dollar" }, value{ 100 } {}

std::string Dollar::get_name()
{
	return name;
}

int Dollar::get_value()
{
	return value;
}
