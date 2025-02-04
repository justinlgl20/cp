t = int(input())
for _ in range(t):
    n = int(input())
    s = input()
    if (n % 2 == 1):
        print(-1);
        continue;
    add_to_start = 0;
    sz = n
    st = 100
    en = 100+n-1
    L = []
    ite = 0
    deleted_from = 0;
    while (len(s) > 0 and ite < 300):
        if (s[0] != s[-1]):
            s = s[1:-1];
            deleted_from+=1;
        elif (s[0] == '1'):
            s = '1'+s[:-1]
            #0th index adding after that is 1
            L.append(0+deleted_from)
            deleted_from += 1;
            ite+=1;
        else:
            L.append(len(s)+deleted_from)
            s = s[1:]+'0'
            deleted_from += 1;
            ite+=1;
    if len(s)>0:
        print(-1)
    else:
        print(len(L))
        print(*L)
