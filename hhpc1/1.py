t = int(input())
for i in range(t):
    n = int(input())
    s = input()
    l = []
    last = s[0]
    length = 0
    for i in range(n):
        if (s[i] == last):
            length+=1;
        else:
            l.append([last, length])
            length = 1;
            last = s[i];
    if (length):
        l.append([last, length]);
    best = 0
    for i in l:
        best = max(best, i[1]+(len(l) > 1));
    if len(l) > 2:
        for i in range(1, len(l)-1):
            if l[i][1] == 1 and l[i-1][0] == l[i+1][0]:
                best = max(best, l[i-1][1]+l[i+1][1] + 1)
    print(best)
