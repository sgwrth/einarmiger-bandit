#pragma once
#include <string>

class coin {
public:
	virtual std::string get_name() = 0;
	virtual int get_value() = 0;
	virtual ~coin() {};
};

