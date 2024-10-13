#ifndef COIN_H
#define COIN_H
#include <string>

class Coin {
public:
	virtual std::string get_name() = 0;
	virtual int get_value() = 0;
	virtual ~Coin() {};
};

#endif
