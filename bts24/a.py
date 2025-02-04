n, m, k = map(int, input().split())
grid = [[i for i in input()] for i in range(n)]
ans = []
for i in grid:
    ans.append([j for j in i]);
for i in range(n):
    l = grid[i]
    last = -100000000
    for j in range(m):
        if (l[j] == 'B'):
            if (j-last)<=k:
                ans[i][j] = 'N'
            else:
                ans[i][j] = 'Y'
        if (l[j] == 'A'):
            last = j;
    last = 100000000
    for j in reversed(range(m)):
        #print(j, l[j]);
        if (l[j] == 'A'):
            #print(i, j, last);
            if (last-j) <= k:
                ans[i][j] = 'N'
            else:
                ans[i][j] = 'Y'
        if (l[j] != '.' and l[j] != 'a'):
            #print(j);
            last = j;
for i in ans:
    print("".join(i))
