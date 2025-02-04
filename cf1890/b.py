t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    s = input()
    t = input()
    works = True;
    for i in range(n-1):
        if (s[i] == s[i+1]): works = False
    if (works):
        print("Yes")
    else:
        works = True;
        for i in range(m-1):
            if (t[i] == t[i+1]): works = False
        if (t[0] != t[-1] or not works):
            print("No")
        else:
            q = t[0];
            g = set()
            for i in range(n-1):
                if s[i] == s[i+1]: g.add(s[i]);
            if (len(g) == 2): print("No")
            elif list(g)[0] == q: print("No")
            else: print("Yes")
