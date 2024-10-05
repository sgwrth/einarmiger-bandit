#include "slotmachine.h"

void slotmachine::insertCoin(player player, coin coin)
{
	player.creditscore.addToBalance(coin);
}
