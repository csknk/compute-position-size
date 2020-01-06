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

void printAccount(Account *account)
{
	if (isatty(fileno(stdout))) {
			// char yellow[]={0x1b,'[','0',';','3', '3', 'm',0};
			const char *highlight = "\x1b[4m";
			char normal[] = {0x1b,'[','0',';','3','9','m',0};
			printf("\n%sAccount capital: %.8Lf\tAccount risk: %.2f%%%s\n",
				highlight,
				account->capital,
				account->riskPercentage,
				normal
			);
	} else {
			printf("Account capital: %.8Lf Account risk: %.2f%%\n",
				account->capital,
				account->riskPercentage
			);
	}


}
