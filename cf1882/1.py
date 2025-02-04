t = int(input())
for i in range(t):
    n = int(input())
    l = [int(i) for i in input().split()]
    cur = 1;
    for i in l:
        if i == cur:
            cur +=1
        cur += 1
    print(cur-1)
