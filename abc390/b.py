import sys
n=int(input())
l=[int(i) for i in input().split()]
rat = l[1]/l[0]
if(rat==0):
	print("No")
	sys.exit()
for i in range(n-1):
	if(l[i+1]/l[i] != rat):
		print("No")
		sys.exit()
print("Yes")
