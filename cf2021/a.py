t = int(input())
for _ in range(t):
    n = int(input())
    l = [int(i) for i in input().split()]
    l = sorted(l)
    ans = (l[0]+l[1])//2;
    for i in range(2, n):
        ans = (ans+l[i])//2
    print(ans)
