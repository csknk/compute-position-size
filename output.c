#include "output.h"

void printTrades(Trade **trades, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		printTrade(trades[i]);
	}
}

void printTrade(Trade *t)
{
	long double maxLoss = (t->position / t->entry) - (t->position / t->stopLoss);
	long double reward = (t->position / t->exit) - (t->position / t->entry);
	printf(
		"\n"
		"Entry\t\t\t%.2f\n"
	       	"Leverage\t\t%.6f\n"
		"Position\t\t%.2f\n"
		"Stop Loss\t\t%.2f\n"
		"Exit\t\t\t%.2f\n"
		"Profit\t\t\t%.8Lf BTC %.2Lf USD\n"
		"Order Cost\t\t%.8Lf\n"
		"Risk\t\t\t%.8Lf\n"
		"Reward\t\t\t%.8Lf\n"
		"Risk:Reward:\t\t%.8Lf\n"
		,
			t->entry,
			t->leverage,
			t->position,
			t->stopLoss,
		       	t->exit,
			t->profit,
			t->profit * t->exit,
			t->cost,
			maxLoss,
			reward,
			reward / maxLoss
	);
	for (size_t i = 0; i < 10; i++) putchar('-');
	putchar('\n');
}

void printAccount(Account *account)
{
	if (isatty(fileno(stdout))) {
			const char *highlight = "\x1b[4;33m";
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
