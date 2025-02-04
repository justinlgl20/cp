from math import factorial
from operator import mul
from functools import reduce
n=int(input())
c = [1 for i in range(10*n+6)];
mod = 998244353;
for i in range(2,10*n+4):
	c[i]=c[i-1]*i;
	c[i]%=mod;

def factorial(e):
	return c[e];

def ans(n):
    s = ''.join(str(i) for i in range(1, n+1))
    return sum(int(d) for d in s)*factorial(len(s)-1)*(10**len(s)-1)//(9*reduce(mul, (factorial(d) for d in (s.count(w) for w in set(s))))) 
print(ans(n)%mod);
