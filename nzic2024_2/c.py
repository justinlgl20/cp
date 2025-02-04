n, a = map(int, input().split())
points = {}



ans = 0;
for i in range(n):
    r, c = map(int, input().split())
    l1 = [r-a, c-a]
    r1 = [r+a+1, c+a+1]
    for q in range(max(0, r-a), r+a+1):
        for w in range(max(0, c-a), c+a+1):
            if q not in points:
                points[q] = {}
            points[q][w] = 1
    """g = min(r1[1], 2*a+1)*(min(r1[0], 2*a+1))
    print(g, r1, l1)
    ans += g
    for j in points:
        l2 = [j[0]-a, j[1]-a]
        r2 = [j[0]+a+1, j[1]+a+1]
        x = (min(r1[0], r2[0])-max(l1[0], l2[0]))
        y = (min(r1[1], r2[1])-max(l1[1], l2[1]));
        print(x, y)
        if (x < 0 or y < 0): continue
        ans -= x*y
    points.append([r, c])"""
for i in points:
    ans += len(points[i])
print(ans)
