t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    if (n <= 60 and k > 2**(n-1)):
        print(-1)
    else:
        front = []
        back = []
        for i in range(0, 
