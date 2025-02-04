t = int(input())
for i in range(t):
    n, an = map(int, input().split())
    if (n % 2 == 0):
        a2 = an;
        a1 = 1;
    else:
        a2 = 1;
        a1 = an;
    print(a1, a2);
