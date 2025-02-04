n = int(input())
if (n%2 == 0):
    for i in range(n//2+1, n+1):
        print(n+1-i, n+1-(i-n//2), end=" ");
    print()
else: #doesn't work
    g = n//2
    #min gap is n//2
    print(1, 1+g, 1+2*g, end=" ")
    for i in range(n//2, 1, -1):
        print(i, i+g, end=" ")
