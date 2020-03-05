# Position Size Calculator
Command line utility designed to quickly calculate position size such that the maximum amount risked in the trade does not exceed a set amount.

By managing trades in this way, you know the maximum amount that you would lose if the trade goes against your expected direction. You need this information before entering a trade.

Description
-----------
Computes position size based on:

* Account capital
* Maximum acceptable risk
* Entry price
* Stop loss

The outputs are:
* Position size
* Leverage

Calculations are roughed out in Python, with the main project being in C.

This is very much a work in progress (I'm currently testing it out) so use at your own risk.

At the moment, the position size is calculated based on margin trading on [Bybit][3].

Build
-----
Navigate to the project repo and run `make`.

Executable is compiled into `bin/trade-position`.

Usage
-----
- Rename the files `sample-account.txt` and `sample-trades.txt` to `account.txt` and `trades.txt` respectively.
- Run the executable

Setting a Stop Loss and Defining Risk
-------------------------------------
__Position Size__ and __Risk Amount__ are not the same.

If the __Capital__ is $1,500 and the desired risk on a trade is 1%, this should mean that if the stop loss is triggered the loss should be limited to $15 (1% of 1,500).

Note that it is probably better to use __Market Stop Loss__ rather than __Limit Stop Loss__ for the sake of safety - to ensure that the stop loss executes.

Stop Loss: Based on Technical Analysis
--------------------------------------
__The stop loss should be based on Technical Analysis - not a fixed percentage.__

Place the stop loss at the invalidation level - the point at which the idea for entering the trade has been invalidated/disproved by the market.

There are reasons for an Entry, and the SL is the point at which these reasons have been nullified.

Risk Per Trade & Position Size
------------------------------

* Definition of Risk Per Trade: The percentage of total equity a trader may lose per trade.
* Definition of Position Size: The number of units of an instrument that a trader purchases.

Risk per Trade - this is by personal preference. In most traders, 2 to 3% risk per trade is common.

Calculate the absolute risk per trade = Capital x Risk per Trade %.

Risking this amount means that if the trade is stopped out, this amount will be lost.

### Position Size
To calculate position size, two pieces of information are required:

* Risk per Trade
* Difference between Entry and Stop Loss

Position Size = (Capital x Risk Percentage) / SL percentage

For example:

* Capital: 100
* Maximum risk: 3%
* Stop Loss: 5%

Position Size = (100 x .03) / .05 = 60

If the position size is 60, the entry price is 100 and the stop loss triggers at a price of 95, the realized loss will be 60 - ((60/100) x 95)

Start: 60 buys 60/100 Units = 0.6
At Stop Loss: 0.6 Units sold at 95 = 0.6 x 95 = 57
Difference between 60 and 57 is 3 - the Risk Amount.
 
TODO
----
This is very much a work in progress - feel free to open an issue for discussion prior to sending a pull request.

Tasks:
* Calculate Risk/Return ratio and expected P/L
* Output to trading log
* Improve "config" files
* Connect to ByBit API

References
----------
* [Trading with Rayner: The Complete Guide to Risk Reward Ratio][1]
* [Risk Management - TA Series][2] - YouTube video, Crypto Cred

[1]: https://www.tradingwithrayner.com/risk-reward-ratio/
[2]: https://www.youtube.com/watch?v=ofwtsc20hOY
[3]: https://www.bybit.com/
