n=int(2e5)
m=int(1e18)
f=open("file.in","w")
print(n,m,file=f)
l=[1 for i in range(n)]
print(*l, file=f)
