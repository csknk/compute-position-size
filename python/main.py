#!/usr/bin/env python3
import trade
import acc
import json, sys

def main(trade_datafile):
    with open(trade_datafile) as file:
            data = json.load(file)

    short = True if data["predicted_exit"] < data["entry"] else False
    a = acc.Account(data["capital"], data["max_loss"])
    t = trade.Trade(data["entry"], data["predicted_exit"], data["stop_loss"], a)
    t.print()

if __name__ == '__main__':
    trade_datafile = sys.argv[1] if len(sys.argv) > 1 else None
    main(trade_datafile)
