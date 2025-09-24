#ifndef CREDITSCORE_H
#define CREDITSCORE_H
#include <memory>
#include <vector>

class Coin;
class Slotmachine;

class Creditscore {
public:
	Creditscore();
	std::vector<std::shared_ptr<Coin>>& get_coins();
	void add_amount_to_balance(long amount);
	void add_to_balance(std::shared_ptr<Coin> coin);
	void process_result(Slotmachine& machine);
	long get_balance() const;
	long compute_balance();
private:
	std::vector<std::shared_ptr<Coin>> coins;
	long balance;
};

#endif
