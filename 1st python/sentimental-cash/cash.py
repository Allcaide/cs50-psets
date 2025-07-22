from cs50 import get_float
import string

coins = [0.25, 0.10, 0.05, 0.01]


while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

total_coins = 0


for i in coins:

    while (change >= i):
        change = round(change - i, 3)
        total_coins += 1


print(total_coins)
