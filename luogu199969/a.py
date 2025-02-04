n, m = map(int, input().split())
a, b, x = map(int, input().split())

def solve(a, b):
    if (a > n or a <= 0 or b > m or b <= 0):
        return 100000000000000000000000000000000000000000000
    hrow = n//2;
    if n%2 == 1 and a%2 == 0:
        hrow += 1;
    ans = m*hrow;
    drow = n-hrow;
    cnt = m//2;
    if (m%2 == 1 and b%2 == 0):
        cnt += 1;
    
    l = drow*cnt;
    ans += l;
    return ans;

if (x == 0):
    print(solve(a, b))
else:
    l = [1, -1, 0, 0]
    ans = solve(a, b)+1;
    for i in l:
        for j in l:
            if (i == 0 and j == 0):
                continue;
            ans = min(ans, solve(a+i, b+j));
    print(ans)
