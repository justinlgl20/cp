t = int(input())
for _ in range(t):
    a, b = map(int, input().split());
    x = b-a
    if (b <= a):
        print(a)
    else:
        print(max(0, a-x))
