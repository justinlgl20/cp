t = int(input())
for _ in range(t):
    n, k, x = map(int, input().split())
    smol = (k*(k+1))/2
    big = n*(n+1)/2
    o = (n-k+1)*(n-k)/2
    if o != 0: big-= o
    if (smol <= x and x <= big): print("YES")
    else: print("NO")

