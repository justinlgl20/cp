N = int(input())
d = [int(i) for i in input().split()]
ans = 0
for i in range(N):
    k = set(list(str(i+1)))
    if (len(k) > 1): continue;
    for j in range(d[i]):
        f = set(list((str(j+1))));
        f = f.union(k);
        if (len(f) == 1): ans+=1;
print(ans)
