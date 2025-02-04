n = int(input())
h = [int(i) for i in input().split()]+[1e9]

nex = [-1 for i in range(n)]
ans = [0 for i in range(n)]
ans2 = ans[:]

l = [-1]
h[-1] = 1e9
for i in range(n-1, -1, -1):
    ans2[i] = len(l)-1
    while len(l) and h[l[-1]] < h[i]:
        l.pop()
    g = l[-1]
    l.append(i)
for i in range(n):
    print(ans[i]+ans2[i], end=" ")
print()
