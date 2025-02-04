t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = [int(i) for i in input().split()]
    w = 0
    for i in range(n):
        q = 0;
        for j in range(n):
            if (i != j):
                q += (abs(a[i]-a[j])%k == 0)
        if (q == 0):
            print("YES");
            print(i+1)
            w = 1
            break;
    if not w:
        print("NO")
