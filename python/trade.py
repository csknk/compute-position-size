class Trade:
    def __init__(self, entry, predicted_exit, stop_loss, account):
        self.entry = entry
        self.stop_loss = stop_loss
        self.predicted_exit = predicted_exit
        self.capital = account.capital
        self.risk = account.risk
        self.set_position()
        self.set_leverage()
        self.cost = self.position
        self.set_order_cost()

    def set_position(self):
        diff_stop_loss = abs(self.entry - self.stop_loss)
        account_risk = (self.capital / 100) * self.risk
        self.position = int(((self.stop_loss * account_risk) / diff_stop_loss) * self.entry)

    def set_leverage(self):
        self.leverage = (self.position / self.entry) / self.capital

    # set cost == capital to start
    def set_order_cost(self):
        # Incrementally reduce the position size until it is affordable
        while (self.cost >= self.capital):
            self.position -= 1
            initial_margin = (self.position / self.entry) * (1 / self.leverage)
            fee_to_open = (self.position / self.entry) * (0.075 / 100)
            bankruptcy_price = (self.entry * self.leverage) / (self.leverage + 1)
            fee_to_close = (self.position / bankruptcy_price) * (0.075 / 100)
            self.cost = initial_margin + fee_to_open + fee_to_close

    def print(self):
        print("Entry: {}".format(self.entry))
        print("Position: {:.0f}".format(self.position))
        print("Leverage: {:.2f}".format(self.leverage))
        print("Stop Loss: {}".format(self.stop_loss))
        print("Cost: {:.8f}".format(self.cost))
        print("Predicted Exit: {}".format(self.predicted_exit))

