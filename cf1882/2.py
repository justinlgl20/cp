t = int(input())
for i in range(t):
    n = int(input())
    l = []
    for i in range(n):
         s= set([int(i) for i in input().split()][1:])
         l.append(s)
    ans = 0
    total = set()
    for i in l: total = total|i

    for i in total:
        #try to remove i
        s = set()
        for j in l:
            if i not in j:
                s = s|j;
        ans = max(ans, len(s))
    print(ans)
