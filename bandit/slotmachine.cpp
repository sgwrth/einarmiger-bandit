#include "slotmachine.h"

void slotmachine::insert_coin(player& player, coin& coin)
{
	player.get_creditscore().add_to_balance(player.get_creditscore().get_coins(), coin);
}
