t = int(input())
for _ in range(t):
    n = int(input())
    s = [i for i in input()]
    c = {}
    for i in s:
        c[i] = c.get(i, 0)+1
    most = 0
    l = "1"
    least = 1e9;
    w = "1"
    for i in c:
        if c[i] > most:
            most = c[i]
            l = i
        if (c[i] < least) or (i != w and w == l):
            least = c[i]
            w = i
    for i in range(n):
        if s[i] == w:
            s[i] = l
            break
    print("".join(s))
