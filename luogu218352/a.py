import math
n,x,k=map(int,input().split())
_k=k;
days=math.ceil(n/x)
ans=0
while (days>0):
	if(k>0):
		ans+=1;
		days-=1;
		k-=1;
	else:
		ans+=1;
		k+=_k;
print(ans);
