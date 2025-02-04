n, t= map(int, input().split())
s = input()
x = [int(i) for i in input().split()]

l = []
for i in range(n):
    l.append([x[i]+1e9, s[i]])

#two pointers sweeping
inx = 0
inx2 = 0
left = 0;
ans = 0
l.append([1e18, 1])
l = sorted(l)
while (inx2 < n and l[inx2][0] <= 2*t):
    if l[inx2][1]=='0':
        left+=1;
    inx2+=1;
for inx in range(n):
    while (inx2 < n and l[inx2][0] <= l[inx][0]+2*t):
        if (l[inx2][1] == '0'):
            left += 1;
        inx2+=1
    if (l[inx][1] == '0'):
        left -= 1
    else:
        ans += left;
        #print(left, l[inx], l[inx2])
print(ans)
