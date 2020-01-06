#ifndef PARAMS_H
#define PARAMS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct _trade {
	float entry;		// USD
	float exit;		// USD
	float stopLoss;		// USD
	double position;	// BTC
	double leverage;	// Factor
	long double profit;	// BTC
	double profitUSD;	// USD
	long double cost;	// BTC
} Trade;


typedef struct _account {
	long double capital;	// BTC
	float riskPercentage;	// Decimal
} Account;

void setAccount(FILE *fp, Account *account);
size_t setTradeSetups(FILE *fp, Trade ***tradeSetups);
void setPosition(Trade *t, Account *a);
void setLeverage(Trade *t, Account *a);
void setProfit(Trade *t);
long double setOrderCost(Trade *t, long double capital);

#endif
