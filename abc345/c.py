s = input()
cnt = {}
for i in s:
    cnt[i] = cnt.get(i, 0)+1
ans = 0
for i in cnt:
    ans = ans or 2*(cnt[i] >= 2)
for i in cnt:
    ans += cnt[i]*(len(s)-cnt[i])
print(ans//2)
