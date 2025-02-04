import sys
l = [int(i) for i in input().split()]
for i in range(4):
	l[i],l[i+1] = l[i+1], l[i]
	if(l==sorted(l)):
		print("Yes")
		sys.exit()
	l[i],l[i+1] = l[i+1], l[i]
print("No")
