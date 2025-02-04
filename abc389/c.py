l=[[0,0]]
minindex=1; # one before start
q=int(input())
for i in range(q):
	qw=input().split()
	if(len(qw)==1):
		a=2;
		b=-1;
	else:
		a,b=qw;
		a=int(a)
		b=int(b)
	if(a==1):
		l.append([l[-1][0]+l[-1][1], b]);
	elif a==2:
		minindex+=1;
	else:
		if minindex+b-1>=len(l):
			print(0);
		else:
			print(l[b-1+minindex][0]-l[minindex][0]);
