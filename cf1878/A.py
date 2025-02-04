t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    L = [int(i) for i in input().split()]
    if k in L:
        print("YES")
    else:
        print("NO")
