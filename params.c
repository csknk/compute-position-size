#include "params.h"

void setAccount(FILE *fp, Account *account)
{
	char *lineBuf = NULL;
	size_t n = 0;
	ssize_t lineLength = 0;
	while((lineLength = getline(&lineBuf, &n, fp)) != -1) {
		if ((lineBuf[0] == '#')) continue;
		sscanf(lineBuf, "%Lf %f", &(account->capital), &(account->riskPercentage));
	}
	free(lineBuf);	
}

size_t setTradeSetups(FILE *fp, Trade ***tradeSetups)
{
	char *lineBuf = NULL;
	size_t n = 0;
	ssize_t lineLength = 0;
	size_t i = 0;
	while((lineLength = getline(&lineBuf, &n, fp)) != -1) {
		if ((lineBuf[0] == '#')) {
			lineBuf = NULL;
			continue;
		}
		Trade **tmp = realloc(*tradeSetups, (sizeof(*tradeSetups) * (i + 1)));
		if(!tmp) {
			perror("realloc failed.");
			exit(EXIT_FAILURE);
		}
		*tradeSetups = tmp;
		// NB sizeof needs to dereference the pointer!!!!!!!!!!!!!!!
		(*tradeSetups)[i] = calloc(1, sizeof(*(*tradeSetups)[i]));
		sscanf(
			lineBuf,
			"%f %f %f",
			&((*tradeSetups)[i]->entry),
			&((*tradeSetups)[i]->exit),
			&((*tradeSetups)[i]->stopLoss)
		);
		i++;
		lineBuf = NULL;
	}
	free(lineBuf);
	return i;
}

void setPosition(Trade *t, Account *a)
{
	// Distance of stop loss from entry.
	float diffStopLoss = t->entry - t->stopLoss;

	// Absolute correction in the case of a short position.
	diffStopLoss = t->entry < t->stopLoss ? diffStopLoss * -1 : diffStopLoss;

	// Account risk in units of instrument (e.g. BTC)
	float accountRisk = (a->capital / 100) * a->riskPercentage;

	// Position is the capital divided by the stop loss as a percentage.
	t->position = ((t->stopLoss * accountRisk) / diffStopLoss) * t->entry;
}

void setLeverage(Trade *t, Account *a)
{
	t->leverage = (t->position / t->entry) / a->capital;
}

void setProfit(Trade *t)
{
	long double end = t->position / t->exit;
	long double start = t->position / t->entry;
	
	t->profit = end - start;
	t->profit = t->profit < 0 ? t->profit * -1 : t->profit;
	t->profitUSD = t->profit * t->exit;
}

long double setOrderCost(Trade *t, long double capital)
{
	if (t->cost < capital)
		return t->cost;

	t->position = t->position - 1;

	long double initialMargin = (t->position / t->entry) * (1 / t->leverage);

	// @TODO change hardcoded value for fee rate
	long double feeToOpen = (t->position / t->entry) * (1 / 100) * 0.075;

	long double bankruptcyPrice = (t->entry * t->leverage) / (t->leverage + 1);

	long double feeToClose = (t->position / bankruptcyPrice) * (1 / 100) * 0.075;

	t->cost = initialMargin + feeToOpen + feeToClose;

	return setOrderCost(t, capital);

}
