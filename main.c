#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "output.h"

int main()
{
	FILE *acFile = fopen("account.txt", "r");
	Account *account = calloc(1, sizeof(*account));
	setAccount(acFile, account);
	fclose(acFile);

	FILE *tradesFile = fopen("trades.txt", "r");
	Trade **tradeSetups = calloc(1, sizeof(*tradeSetups));
	size_t nTrades = setTradeSetups(tradesFile, &tradeSetups);
	fclose(tradesFile);

	for (size_t i = 0; i < nTrades; i++) {
		setPosition(*(tradeSetups + i), account);
		setLeverage(*(tradeSetups + i), account);
		setProfit(*(tradeSetups + i));
		(*(tradeSetups + i))->cost = account->capital;
		setOrderCost(*(tradeSetups + i), account->capital);
	}
	printAccount(account);
	printTrades(tradeSetups, nTrades);
	
	for (size_t i = 0; i < nTrades; i++) {
		free(tradeSetups[i]);
	}
	free(tradeSetups);
	free(account);
	return 0;
}
