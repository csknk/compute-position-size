#!/usr/bin/env python3

def main():
    # -------------
    capital = 0.24248526
    max_loss = 1
    entry = 7295
    stop_loss = 7260
    predicted_exit = 7400
    short = True if predicted_exit < entry else False
    # -------------
    max_loss /= 100                     # For percentage calculations
    risk_amount = capital * max_loss
    distance_to_stop_loss = abs(entry - stop_loss)
    proportional_distance_to_stop_loss = distance_to_stop_loss / entry
    position_size = risk_amount * stop_loss / proportional_distance_to_stop_loss
    position_size = int(position_size)
    leverage = position_size / (capital * entry)

    abs_max_loss = abs((position_size / stop_loss) - (position_size / entry))

    print("position_size:\t\t{}\nleverage:\t\t{:.2f}".format(position_size, leverage))
    print("abs_max_loss:\t\t{}".format(abs_max_loss))
    print("max_loss (USD):\t\t{:.2f}".format(abs_max_loss * stop_loss))
    print("check max loss (USD):\t{:.2f}".format(capital * stop_loss * max_loss))
    
    

if __name__ == '__main__':
    main()
