t = int(input())
for _ in range(t):
    n = int(input())
    a = [int(i) for i in input().split()]
    if len(set(a)) > 2:
        print("No")
    else:
        if (a.count(a[0]) == n//2 or (n % 2 == 1 and a.count(a[0]) == n//2+1)) or len(set(a)) == 1:
            print("Yes")
        else:
            print("No")
