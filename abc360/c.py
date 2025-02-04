n = int(input())
a = [int(i) for i in input().split()]
w = [int(i) for i in input().split()]

l = [[] for i in range(n+2)]
for i in range(n):
    l[a[i]].append(w[i])
ans = sum(w);
for i in range(n+2):
    l[i] = sorted(l[i]);
    if (len(l[i]) > 0):
        ans -= max(l[i]);
print(ans)
