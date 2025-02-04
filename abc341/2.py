n = int(input())
l = [int(i) for i in input().split()]
s, t = [0 for i in range(n)], [0 for i in range(n)]

for i in range(n-1):
  a,b = map(int, input().split())
  s[i], t[i] = a, b;
  if True:
    g = l[i]//s[i]
    l[i] %= s[i];
    l[i+1] += t[i]*g;
print(l[n-1])
