#include <iostream>
#include "coin.h"
#include "slotmachine.h"

void slotmachine::insert_coin(player& player, coin& coin)
{
	player.get_creditscore().add_to_balance(player.get_creditscore().get_coins(), coin);
	std::cout << player.get_creditscore().coins.size() << "\n";
	std::cout << coin.get_value() << " zum Guthaben hinzugefuegt. "
			<< "Neuer Kontostand: " << player.get_creditscore().compute_balance() << "\n";
}
