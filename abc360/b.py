import sys
s, t = input().split()
for i in range(1, len(s)): # w
    x = []
    for j in range(0, len(s), i):
        x.append(s[j:j+i])
    for j in range(0, min(i, len(s))): #c
        q = ""
        for w in x:
            if (len(w) > j):
                q += w[j]
        if q == t:
            print("Yes")
            sys.exit()
print("No")
