t = int(input())
for _ in range(t):
    n = int(input())
    l = [int(i) for i in input().split()]
    yr = l[0]
    for i in range(1, n):
        g = ((yr+1)//l[i] + ((yr+1)%l[i] > 0))*l[i]
        yr = g
    print(yr)
