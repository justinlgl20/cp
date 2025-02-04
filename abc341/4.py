import sys
n, m, k = map(int, input().split())

def gcd(a, b):
    if (a == 0):
        return b;
    return gcd(b%a, a)

lcm = n*m//gcd(n, m);
u = lcm//n + lcm//m - 2
fl = lcm*(k//u - (k%u == 0))
k = k - (k//u - (k % u == 0)) * u
i = 2**30
val = 0
while i > 0:
    if (val+i < lcm//n):
        no = (val+i)*n
        cnt = no//m + val + i
        if (cnt <= k):
            val += i
    i //= 2;
g = val*n
cnt = g//m + val
if (cnt != k):
    n, m = m, n
else:
    #print("left after", fl, "is", k)
    #print("used", val, "ns")
    print(val*n + fl)
    sys.exit()
i = 2**30
val = 0
while i > 0:
    if (val+i < lcm//n):
        no = (val+i)*n
        cnt = no//m + val + i
        if (cnt <= k):
            val += i
    i //= 2;
print(int(val*n + fl))
