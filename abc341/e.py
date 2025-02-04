n, q = map(int, input().split())
s = input()
bad = set()
for i in range(n-1):
    if (s[i] != s[i+1]):
        bad.add(i)
for _ in range(q):
    a, b, c = map(int, input().split())
    if a == 1:
        if b != 0 and b-1 in bad:
            bad.erase(b-1)
        else:
            bad.add(b-1);
        if c != n-1 and c in bad:
            bad.erase(c)
        else:
            bad.add(c)
    else:
        if len(bad) > 0:
            print("No")
        else:
            print("Yes")
