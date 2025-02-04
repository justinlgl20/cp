t = int(input())

for i in range(t):
    n = int(input())
    l = [int(i) for i in input().split()]
    losing_poses = []
    lowest = 1e9;
    for i in range(n):
        if l[i] < lowest:
            losing_poses.append(i);
            lowest = l[i]
    lowest_losing = 1e9;
    lowest_winning = 1e9;
    ans = 0;
    lo = [0 for i in range(n)]
    for i in range(n):
        #print(i, ": ", lowest_losing, lowest_winning)
        if l[i] < lowest_losing:
            lo[i] = 1;
            lowest_losing = l[i];
        elif l[i] > lowest_losing and l[i] < lowest_winning:
            #winning
            lowest_winning = l[i];
            ans += 1;
        else:
            lowest_losing = min(lowest_losing, l[i]);
    print(ans)


