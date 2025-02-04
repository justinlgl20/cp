t = int(input())
for _ in range(t):
    k = int(input())
    ans = 0
    for i in range(100):
        if k % 2**(ans+1) == 0:
            ans+=1
    if k == 0:
        print("NO!");
    else:
        print(ans+1);
