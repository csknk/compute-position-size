#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "params.h"
#include "output.h"

int main()
{
	FILE *acFile = fopen("account.txt", "r");
	Account *account = calloc(1, sizeof(*account));
	setAccount(acFile, account);
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

	FILE *tradesFile = fopen("trades.txt", "r");
	
	Trade **tradeSetups = calloc(1, sizeof(*tradeSetups));
	
	size_t nTrades = setTradeSetups(tradesFile, &tradeSetups);
	
	for (size_t i = 0; i < nTrades; i++) {
		setPosition(*(tradeSetups + i), account);
		setLeverage(*(tradeSetups + i), account);
		setProfit(*(tradeSetups + i));
		(*(tradeSetups + i))->cost = account->capital;
		setOrderCost(*(tradeSetups + i), account->capital);
	}
	printTrades(tradeSetups, nTrades);
	
	for (size_t i = 0; i < nTrades; i++) {
		free(tradeSetups[i]);
	}
	free(tradeSetups);
	free(account);
	return 0;
}
