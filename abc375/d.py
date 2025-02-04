s = input()
loc = {i:[] for i in set(s)}
for i in range(len(s)):
    loc[s[i]].append(i)

ans = 0
for i in loc:
    l = loc[i];
    s = l[0]+1
    for i in range(1, len(l)):
        ans += l[i]*(i) - s
        s += l[i]+1;
print(ans)
