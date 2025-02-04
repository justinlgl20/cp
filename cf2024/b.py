t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = [int(i) for i in input().split()]
    a = sorted(a)
    height = 0;
    cur = 0;
    ans = k;
    things = n;
    for i in a:
        add = things*(i-height)
        if (cur + add >= k):
            print(ans)
            break;
        else:
            ans += 1;
            cur += add
        height = i;
        things-=1;
