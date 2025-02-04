x, y = map(int, input().split())
if (x > y and x-y <= 3) or (x < y and y-x <= 2): print("Yes")
else:
    print("No")
