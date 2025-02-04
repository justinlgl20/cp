n = int(input())
a = [int(i) for i in input().split()]

q = a[:]
for i in range(n):
    q[i] -= i;
ans = [-1e9 for i in range(n)]

def query(l, r):
    if (l > r):
        return [-1e9, -1];
    m = -1e9;
    inx = -1;
    for i in range(l, r+1):
        if (q[i] > m):
            m = q[i];
            inx = i;
    return [m, inx]
print(q)
print(a)
for i in range(n):
    # GET MAX IN RANGE(i+a[i], i-1);
    m, inx = query(i+a[i], n-1);
    print(i, m, inx, i+a[i], n-1);
    if (m >= -i):
        ans[i] = inx-i;
print(ans)
