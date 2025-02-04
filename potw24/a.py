n=int(input())
a=input()
zeros=a.count("A");
ones=a.count("B");
if(abs(zeros-ones)>1):
	print("N")
else:
	print("Y");
