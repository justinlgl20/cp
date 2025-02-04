import math
t = int(input())
for _ in range(t):
    n = int(input())
    l = [int(i) for i in input().split()]
    x = [l[0]];
    for i in range(1, n):
        x.append(x[-1]+l[i]);
    ans = 0
    for i in x:
        if (math.floor(i**(0.5))**2 == i and math.floor(i**(0.5)) % 2 == 1):
            ans+=1;
    print(ans)
