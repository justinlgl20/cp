import sys
input = sys.stdin.readline 

n, m, q = map(int, input().split())
a = [[int(i) for i in input().split()] for i in range(n)]
loc = {}
for i in range(n):
    for j in range(m):
        loc[a[i][j]] = [i, j]

for i in range(q):
    k, r1, c1, r2, c2 = map(int, input().split())
    if r1 <= loc[k][0] and loc[k][0] <= r2 and c1 <= loc[k][1] and loc[k][1] <= c2:
        print("yes")
    else:
        print("no")