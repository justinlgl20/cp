t = int(input())
for _ in range(t):
    w, b = map(int, input().split())
    #bsearch on answer
    ans = 0
    for i in range(32, -1, -1):
        n = ans + 2**i;
        x = n*(n+1)//2;
        if (w+b >= x):
            ans += 2**i
    print(ans)
