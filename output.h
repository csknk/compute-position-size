#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdlib.h>
#include <stdio.h>
#include "params.h"

void printTrade(Trade *t);
void printTrades(Trade **trades, size_t n);

#endif
