t = int(input())
for _ in range(t):
    n = int(input())
    s = input()
    x = s.find("**")
    if x == -1:
        x = n;
    ans = 0
    for i in range(x):
        ans += s[i] == "@"
    print(ans)
