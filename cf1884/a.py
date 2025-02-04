t = int(input())
for i in range(t):
    n, k = map(int, input().split())
    g = [0]+[int(i) for i in str(n)]
    if (sum(g) % k == 0):
        print(n)
    else:
        to_add = (k*(sum(g)//k+1))-sum(g);
        while sum(g) % k != 0:
            n += 1;
            g = [int(i) for i in str(n)]
        print(n)
