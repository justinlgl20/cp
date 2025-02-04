t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = [int(i) for i in input().split()]
    if n >= 3:
        if k >= 1:
            ans = max(a)*n;
        else:
            # ans is what it already is
            ans = 0;
            ma = 0;
            for i in range(n):
                ma = max(ma, a[i]);
                ans += ma;
    else:
        if k%2 == 1:
            a = [a[1], a[0]]
        ans = a[0] + max(a[1], a[0]);
    print(ans)
