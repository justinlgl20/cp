import math
N = int(input())
a = [int(i) for i in input().split()]
if N > 15:
    print(1+(a[0] == 1), N-(a[N-1]==1))
else:
    start = 1
    end = 1
    pos = 0;
    for i in range(N):
        start *= a[i]
        if a[i] == 1:
            pos = i
            break
    if pos == 0: start = -1e9
    else: start = start/pos
    for i in range(N-1, -1, -1):
        end *= a[i]
        if a[i] == 1:
            assert(i == pos)
            break
    if N-pos-1 == 0: end = -1e9
    else: end = end/(N-pos-1)
    total = math.factorial(N-1)
    if max([total, start, end]) == total:
        print(1, N)
    elif max([total, start, end]) == start:
        print(1, pos)
    else:
        print(pos+2, N)
 
