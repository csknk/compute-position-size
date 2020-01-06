#include "output.h"

void printTrades(Trade **trades, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		printTrade(trades[i]);
	}
}

void printTrade(Trade *t)
{
	printf("Entry: %.2f Exit: %.2f Stop Loss: %.2f Position: %.2f Leverage: %.6f Profit: %.8Lf BTC %.2Lf USD Cost: %.8Lf\n",
			t->entry,
		       	t->exit,
			t->stopLoss,
			t->position,
			t->leverage,
			t->profit,
			t->profit * t->exit,
			t->cost
		);
}
