from math import *
t=int(input())
for _ in range(t):
	l,r=map(int,input().split());
	ans=r-l;
	if(l==r and gcd(l,r)==1):
		ans+=1;
	print(ans)
