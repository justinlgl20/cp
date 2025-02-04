n, t, p = map(int, input().split())
l = [int(i) for i in input().split()]

l = sorted(l)
print(max(t-l[n-p], 0))
