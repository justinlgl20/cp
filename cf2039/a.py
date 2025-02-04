t = int(input())
l = [1]
for i in range(2, 105):
    l.append(i+i-1);
for i in range(t):
    n = int(input())
    print(*l[:n])

