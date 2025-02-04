def solve(n):
    count = 0
    for m in range(1, n):
        if (n * m) % (n - m) == 0:
            count += 1
    return count
T = int(input())
for _ in range(T):
    n = int(input())
    print(1);
