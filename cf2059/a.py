t=int(input())
for _ in range(t):
	n=int(input())
	a=set([int(i) for i in input().split()])
	b=set([int(i) for i in input().split()])
	if(len(a)*len(b)>=3):
		print("Yes")
	else:
		print("No")
