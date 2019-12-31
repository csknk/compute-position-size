#ifndef PARAMS_H
#define PARAMS_H


typedef struct _trade {
	float entry;		// USD
	float exit;		// USD
	float stopLoss;		// USD
	double position;	// BTC
} Trade;

void printTrade(Trade *t);

typedef struct _account {
	long double capital;	// BTC
	float riskPercentage;	// Decimal
} Account;

void setAccount(FILE *fp, Account *account)
{
	char *lineBuf = NULL;
	size_t n = 0;
	ssize_t lineLength = 0;
	while((lineLength = getline(&lineBuf, &n, fp)) != -1) {
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
		Trade **tmp = realloc(*tradeSetups, (sizeof(**tradeSetups) * (i + 1)));
		if(!tmp) {
			perror("realloc failed.");
			exit(EXIT_FAILURE);
		}
		*tradeSetups = tmp;
		(*tradeSetups)[i] = calloc(1, sizeof((*tradeSetups)[i]));
		sscanf(
			lineBuf,
			"%f %f %f",
			&((*tradeSetups)[i]->entry),
			&((*tradeSetups)[i]->exit),
			&((*tradeSetups)[i]->stopLoss)
		);
		(*tradeSetups)[i]->position = 0.0;
		i++;
		lineBuf = NULL;
	}
	free(lineBuf);
	return i;
}

void printTrades(Trade **trades, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		printTrade(trades[i]);
	}
}

void printTrade(Trade *t)
{
	printf("Entry: %.2f\t Exit: %.2f\tstopLoss: %.2f\tposition: %.2f\n",
			t->entry,
		       	t->exit,
			t->stopLoss,
			t->position
		);
}

void setPosition(Trade *t, Account *a)
{
	float diffStopLoss = (t->entry - t->stopLoss) / t->entry;
	diffStopLoss = t->entry < t->stopLoss ? diffStopLoss * -1 : diffStopLoss;
	t->position = (t->entry * a->capital) / (diffStopLoss * 100);
}

#endif
