t = int(input())
for _ in range(t):
    n, m, k, p = map(int, input().split());
    if m-p//n >= k:
        print("Together")
    elif n*m-p >= k and k <= m:
        print("Chance")
    else:
        print("Divide")
