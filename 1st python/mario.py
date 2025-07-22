from cs50 import get_int


height = get_int("Height: ")

while (height > 8 or height < 1):
    height = get_int("Height: ")

a = height - 1
b = 1
while (height != 0):
    for i in range(a):
        print(" ", end="")

    for j in range(b):
        print("#", end="")

    print()

    height = height - 1
    a = a-1
    b = b+1
