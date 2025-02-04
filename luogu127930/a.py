x, y, p, q = map(int, input().split())
ans = min(p, x-p, q, y-q)
print(ans)
