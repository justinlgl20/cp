n, k = map(int, input().split())
s = input()
import math
counts = []

l = sorted(s)
print(l)
c = 0
p = l[0]
for i in l:
    if (p == i):
        c+=1
    else:
        counts.append(c)
        c = 1
        p = i
if c != 0:
    counts.append(c)

two_pairs = 0;
for i in counts:
    two_pairs += i//2

ans = 1
for i in range(k//2):
    ans *= two_pairs;
    two_pairs-=1;
if (k%2 == 1):
    ans*= n-k
# ans is number of possible 
print(-ans)

"""
import itertools

g = itertools.permutations(s)
ans = 0
for i in set(g):
    i = list(i)
    bad = 1
    for j in range(0, n-k+1):
        if (i[j:j+k] == i[j:j+k][::-1]):
            bad = 0
    ans += bad
print(ans)
"""
