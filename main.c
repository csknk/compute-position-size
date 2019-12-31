#include <stdio.h>
#include <stdlib.h>
#include "params.h"

int main()
{
	FILE *acFile = fopen("account.txt", "r");
	Account *account = calloc(1, sizeof(*account));
	setAccount(acFile, account);
	printf("account capital: %.8Lf\t account risk: %.2f%%\n",
			account->capital,
			account->riskPercentage * 100
			);

	FILE *tradesFile = fopen("trades.txt", "r");
	
	Trade **tradeSetups = calloc(1, sizeof(*tradeSetups));
	
	size_t nTrades = setTradeSetups(tradesFile, &tradeSetups);
	
	for (size_t i = 0; i < nTrades; i++) {
		setPosition(*(tradeSetups + i), account);
	}
	printTrades(tradeSetups, nTrades);
	
	for (size_t i = 0; i < nTrades; i++) {
		free(tradeSetups[i]);
	}
	free(tradeSetups);
	free(account);
	return 0;
}
