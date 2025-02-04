import io, os
input = io.BytesIO(os.read(0,  os.fstat(0).st_size)).readline 

t = int(input().decode())
for _ in range(t):
    n, m = map(int, input().decode().split())
    a = [int(i) for i in input().decode().strip().split()]
    pro = 1
    for i in a: pro *= i;
    s = input().decode().strip()
    ans = []
    l = 0
    r = n-1
    for i in s:
        ans.append(pro%m)
        if i == 'L':
            pro //= a[l]
            l += 1;
        else:
            pro //= a[r]
            r -= 1
    print(*ans)

