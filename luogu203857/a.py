n, k = map(int, input().split())
l = [int(i) for i in input().split()]
if len(set([i%k for i in l])) == 1:
    ans = 0
    x = max(l)
    for i in l:
        ans += (x-i)//k;
    print("YES", ans)
else:
    print("NO")

