t = int(input())
from math import *
l = []
for _ in range(t):
    n = int(input())
    if n == 1:
        print(1)
    elif n <= 4:
        print(2)
    else:
        used = 2
        filled = 4
        while filled < n:
            filled = 2*(filled+1)
            used+=1
        print(used)
