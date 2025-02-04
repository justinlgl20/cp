n, m = map(int, input().split())
a = [int(i) for i in input().split()]
b = [int(i) for i in input().split()]
cur = 0;
l = [0 for i in range(m+10)]

def add(tl, tr, x):
    if (tl > tr): return 0;
    l[tl]+=x
    l[tr+1]-=x;
for i in range(n):
    #cur to cur + b[i] inclusive
    if (cur + b[i] > m-1):
        # add cur to m-1 inclusive
        add(cur, m-1, a[i]);
        # add 0 to (cur+b[i])%m
        add(0, (cur+b[i])%m-1, a[i]);
    else:
        add(cur, (cur+b[i]-1), a[i]);
    cur = (cur+b[i])%m
ans = [0 for i in range(m)]
cnt = 0;
for i in range(m):
    cnt += l[i]
    ans[i] = cnt;
print(" ".join([str(i) for i in ans]));
