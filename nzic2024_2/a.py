x, y, a, b = map(int, input().split())
ans = max((x//a)*(y//b), (x//b)*(y//a))
print(ans)
